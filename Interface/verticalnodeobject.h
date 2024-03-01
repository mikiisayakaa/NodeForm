#pragma once

//classic blender-like node layout
/*
 *            NodeName
 *                      outputName1 O
 *            outputGetter (optional)
 *                      outputName2 O
 *            outputGetter (optional)
 *
 * O inputName1:
 *   inputSetter (optional)
 * O inputName2:
 *   inputSetter (optional)
 */

//requirement of inputWidget list and outputWidget list

//eval node:
//input[0]: slot handler
//input[1]: slot name label
//input[2]: slot input setter
//output[0]: slot handler
//output[1]: slot name label
//output[2]: slot output getter

#include "Core/abstractnode.h"
#include "abstractnodeobject.h"
#include "Global/globaluiparams.h"

#include <QObject>

namespace Nodest{


class VerticalNodeObject : public AbstractNodeObject
{
    Q_OBJECT
public:
    explicit VerticalNodeObject(AbstractNode* node,NodestGlobal::UIParameters* params,
                                QObject *parent = nullptr);

    void createWidgets();

    void addExtensions();

    void setWidgetsLayout();

    VerticalNodeObject* clone();

signals:

public slots:
    void onInputChanged();


private:


private:
    NodestGlobal::UIParameters* m_createParams;
};

}
