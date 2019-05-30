#include "vapor/VolumeIsoRenderer.h"
#include <vapor/VolumeIsoParams.h>

#include <vapor/MatrixManager.h>
#include <vapor/GLManager.h>
#include <vapor/glutil.h>
#include <glm/glm.hpp>

#include <vapor/VolumeRegular.h>
#include <vapor/VolumeCellTraversal.h>


using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;

using namespace VAPoR;

static RendererRegistrar<VolumeIsoRenderer> registrar( VolumeIsoRenderer::GetClassType(),
                                                VolumeIsoParams::GetClassType() );


VolumeIsoRenderer::VolumeIsoRenderer( const ParamsMgr*    pm,
                        std::string&        winName,
                        std::string&        dataSetName,
                        std::string&        instName,
                        DataMgr*            dataMgr )
          : VolumeRenderer(  pm,
                        winName,
                        dataSetName,
                        VolumeIsoParams::GetClassType(),
                        VolumeIsoRenderer::GetClassType(),
                        instName,
                        dataMgr )
{
    // An ugly fix but I don't think we have a mechanism for this
    if (_needToSetDefaultAlgorithm()) {
        VolumeParams *vp = (VolumeParams*)GetActiveParams();
        Grid *grid = _dataMgr->GetVariable(vp->GetCurrentTimestep(), vp->GetVariableName(), vp->GetRefinementLevel(), vp->GetCompressionLevel());
        if (grid) {
            string algorithmName = _getDefaultAlgorithmForGrid(grid);
            vp->SetAlgorithm(algorithmName);
            delete grid;
        } else {
            vp->SetAlgorithm(VolumeRegularIso::GetName());
        }
    }
}

VolumeIsoRenderer::~VolumeIsoRenderer()
{
}

bool VolumeIsoRenderer::_usingColorMapData() const
{
    return !GetActiveParams()->UseSingleColor();
}

void VolumeIsoRenderer::_setShaderUniforms(const ShaderProgram *shader, const bool fast) const
{
    VolumeRenderer::_setShaderUniforms(shader, fast);
    
    VolumeIsoParams *vp = (VolumeIsoParams *)GetActiveParams();
    
    vector<double> isoValuesD = vp->GetIsoValues();
    vector<float> isoValues(isoValuesD.begin(), isoValuesD.end());
    vector<bool> enabledIsoValues = vp->GetEnabledIsoValues();
    shader->SetUniformArray("isoValue", 4, isoValues.data());
    shader->SetUniform("isoEnabled[0]", (bool)enabledIsoValues[0]);
    shader->SetUniform("isoEnabled[1]", (bool)enabledIsoValues[1]);
    shader->SetUniform("isoEnabled[2]", (bool)enabledIsoValues[2]);
    shader->SetUniform("isoEnabled[3]", (bool)enabledIsoValues[3]);
    if (_cache.constantColor.size() == 4)
        shader->SetUniform("constantColor", *(vec4*)_cache.constantColor.data());
}

std::string VolumeIsoRenderer::_getDefaultAlgorithmForGrid(const Grid *grid) const
{
    const RegularGrid* regular = dynamic_cast<const RegularGrid*>(grid);
    if (regular)
        return VolumeRegularIso::GetName();
    return VolumeCellTraversalIso::GetName();
}

void VolumeIsoRenderer::_getLUTFromTF(const MapperFunction *tf, float *LUT) const
{
    tf->makeLut(LUT);
}
