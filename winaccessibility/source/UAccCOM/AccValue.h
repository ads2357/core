/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#ifndef INCLUDED_WINACCESSIBILITY_SOURCE_UACCCOM_ACCVALUE_H
#define INCLUDED_WINACCESSIBILITY_SOURCE_UACCCOM_ACCVALUE_H

#include "resource.h"           // main symbols

#include <com/sun/star/uno/reference.hxx>
#include <com/sun/star/accessibility/XAccessibleValue.hpp>
#include "UNOXWrapper.h"

/**
 * CAccValue implements IAccessibleValue interface.
 */
class CAccValue :
            public CComObjectRoot,
            public CComCoClass<CAccValue,&CLSID_AccValue>,
            public IAccessibleValue,
            public CUNOXWrapper
{
public:
    CAccValue()
    {
            }
    virtual ~CAccValue()
    {
            }

    BEGIN_COM_MAP(CAccValue)
    COM_INTERFACE_ENTRY(IAccessibleValue)
    COM_INTERFACE_ENTRY(IUNOXWrapper)
    COM_INTERFACE_ENTRY_FUNC_BLIND(NULL,_SmartQI)
    END_COM_MAP()

    static HRESULT WINAPI _SmartQI(void* pv,
                                   REFIID iid, void** ppvObject, DWORD_PTR)
    {
        return ((CAccValue*)pv)->SmartQI(iid,ppvObject);
    }

    HRESULT SmartQI(REFIID iid, void** ppvObject)
    {
        if( m_pOuterUnknown )
            return OuterQueryInterface(iid,ppvObject);
        return E_FAIL;
    }

    DECLARE_NO_REGISTRY()

public:
    // IAccessibleValue

    // Returns the value of this object as a number.
    STDMETHOD(get_currentValue)(VARIANT *currentValue);

    // Sets the value of this object to the given number.
    STDMETHOD(setCurrentValue)(VARIANT value);

    // Returns the maximal value that can be represented by this object.
    STDMETHOD(get_maximumValue)(VARIANT *maximumValue);

    // Returns the minimal value that can be represented by this object.
    STDMETHOD(get_minimumValue)(VARIANT *mininumValue);

    // Override of IUNOXWrapper.
    STDMETHOD(put_XInterface)(hyper pXInterface);

private:

    css::uno::Reference<css::accessibility::XAccessibleValue> pRXVal;

    inline css::accessibility::XAccessibleValue* GetXInterface()
    {
        return pRXVal.get();
    }

};

#endif // INCLUDED_WINACCESSIBILITY_SOURCE_UACCCOM_ACCVALUE_H

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
