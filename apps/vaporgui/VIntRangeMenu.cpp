#include "VIntRangeMenu.h"
#include "VActions.h"

VIntRangeMenu::VIntRangeMenu( 
    QWidget* parent, 
    bool sciNotation, int decimalDigits,
    int min, int max 
    ) 
    : VNumericFormatMenu( parent, sciNotation, decimalDigits ),
      _minRangeAction( new VIntLineEditAction( "Minimum value", min ) ),
      _maxRangeAction( new VIntLineEditAction( "Maximum value", max ) )
{
    connect( _minRangeAction, &VIntLineEditAction::ValueChanged,
        this, &VIntRangeMenu::_minChanged);
    addAction( _minRangeAction );

    connect( _maxRangeAction, &VIntLineEditAction::ValueChanged,
        this, &VIntRangeMenu::_maxChanged);
    addAction( _maxRangeAction );
}

void VIntRangeMenu::SetMinRange( int min ) { 
    _minRangeAction->SetValue( min ); 
}

void VIntRangeMenu::SetMaxRange( int max ) { 
    _maxRangeAction->SetValue( max ); 
}

void VIntRangeMenu::_minChanged( int min ) { 
    emit MinChanged( min ); 
}

void VIntRangeMenu::_maxChanged( int max ) { 
    emit MaxChanged( max ); 
}
