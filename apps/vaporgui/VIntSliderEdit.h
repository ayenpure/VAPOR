#pragma once

#include <string>
#include "VContainer.h"
#include "VAbstractSliderEdit.h"

class VIntRangeMenu;
class VIntLineEdit;
class VIntLineEditAction;

class VIntSliderEdit : public VAbstractSliderEdit {
    Q_OBJECT

public:
    VIntSliderEdit( int min=0, int max=10, int value=3 );

    void SetValue( int value );
    void SetMinimum( int min );
    void SetMaximum( int max );

    int GetValue() const;
    int GetMinimum() const;
    int GetMaximum() const;
    
    virtual int  GetNumDigits() const;
    virtual void SetNumDigits( int numDigits );

    virtual bool GetSciNotation() const;
    virtual void SetSciNotation( bool sciNotation );

    virtual void ShowContextMenu( const QPoint& pos );

protected:
    virtual void _makeContextMenu();
    void _sliderChanged( int value );
    void _sliderChangedIntermediate( int value );

    int _value;    

    VIntRangeMenu*      _menu;
    VIntLineEdit*       _lineEdit;

signals:
    void ValueChanged( int value );
    void ValueChangedIntermediate( int value );
    void MinimumChanged( int min );
    void MaximumChanged( int max );
};
