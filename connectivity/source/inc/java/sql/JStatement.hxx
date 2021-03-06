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
#ifndef INCLUDED_CONNECTIVITY_SOURCE_INC_JAVA_SQL_JSTATEMENT_HXX
#define INCLUDED_CONNECTIVITY_SOURCE_INC_JAVA_SQL_JSTATEMENT_HXX

#include "java/lang/Object.hxx"
#include <com/sun/star/sdbc/XStatement.hpp>
#include <com/sun/star/sdbc/XWarningsSupplier.hpp>
#include <com/sun/star/sdbc/XMultipleResults.hpp>
#include <com/sun/star/sdbc/XBatchExecution.hpp>
#include <com/sun/star/sdbc/XCloseable.hpp>
#include <com/sun/star/util/XCancellable.hpp>
#include <com/sun/star/sdbc/XGeneratedResultSet.hpp>
#include <comphelper/proparrhlp.hxx>
#include <cppuhelper/compbase.hxx>
#include <comphelper/uno3.hxx>
#include <connectivity/CommonTools.hxx>
#include <connectivity/OSubComponent.hxx>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <comphelper/broadcasthelper.hxx>

#include <java/sql/Connection.hxx>
#include "java/sql/ConnectionLog.hxx"

namespace connectivity
{

        typedef ::cppu::WeakComponentImplHelper<       css::sdbc::XStatement,
                                                       css::sdbc::XWarningsSupplier,
                                                       css::util::XCancellable,
                                                       css::sdbc::XCloseable,
                                                       css::sdbc::XGeneratedResultSet,
                                                       css::sdbc::XMultipleResults> java_sql_Statement_BASE;

    //************ Class: java.sql.Statement

    class java_sql_Statement_Base : public comphelper::OBaseMutex,
                                    public  java_sql_Statement_BASE,
                                    public  java_lang_Object,
                                    public  ::cppu::OPropertySetHelper,
                                    public  ::comphelper::OPropertyArrayUsageHelper<java_sql_Statement_Base>

    {

        sal_Int32 getQueryTimeOut()             throw(css::sdbc::SQLException, css::uno::RuntimeException);
        sal_Int32 getMaxFieldSize()             throw(css::sdbc::SQLException, css::uno::RuntimeException);
        sal_Int32 getMaxRows()                  throw(css::sdbc::SQLException, css::uno::RuntimeException);
        sal_Int32 getResultSetConcurrency()     throw(css::sdbc::SQLException, css::uno::RuntimeException);
        sal_Int32 getResultSetType()            throw(css::sdbc::SQLException, css::uno::RuntimeException);
        sal_Int32 getFetchDirection()           throw(css::sdbc::SQLException, css::uno::RuntimeException);
        sal_Int32 getFetchSize()                throw(css::sdbc::SQLException, css::uno::RuntimeException);
        OUString getCursorName()         throw(css::sdbc::SQLException, css::uno::RuntimeException);

        void setQueryTimeOut(sal_Int32 _par0)                   throw(css::sdbc::SQLException, css::uno::RuntimeException);
        void setMaxFieldSize(sal_Int32 _par0)                   throw(css::sdbc::SQLException, css::uno::RuntimeException);
        void setMaxRows(sal_Int32 _par0)                                throw(css::sdbc::SQLException, css::uno::RuntimeException);
        void setResultSetConcurrency(sal_Int32 _par0)   throw(css::sdbc::SQLException, css::uno::RuntimeException);
        void setResultSetType(sal_Int32 _par0)                  throw(css::sdbc::SQLException, css::uno::RuntimeException);
        void setFetchDirection(sal_Int32 _par0)                 throw(css::sdbc::SQLException, css::uno::RuntimeException);
        void setFetchSize(sal_Int32 _par0)                              throw(css::sdbc::SQLException, css::uno::RuntimeException);
        void setCursorName(const OUString &_par0) throw(css::sdbc::SQLException, css::uno::RuntimeException);
        void setEscapeProcessing(bool _par0) throw(css::sdbc::SQLException, css::uno::RuntimeException);

    protected:
        css::uno::Reference< css::sdbc::XStatement>       m_xGeneratedStatement;
        java_sql_Connection*        m_pConnection;
        java::sql::ConnectionLog    m_aLogger;
        OUString             m_sSqlStatement;
        // Properties
        sal_Int32                   m_nResultSetConcurrency;
        sal_Int32                   m_nResultSetType;
        bool                    m_bEscapeProcessing;


    // Static data for the class
        static jclass theClass;

        // OPropertyArrayUsageHelper
        virtual ::cppu::IPropertyArrayHelper* createArrayHelper( ) const override;
        // OPropertySetHelper
        virtual ::cppu::IPropertyArrayHelper & SAL_CALL getInfoHelper() override;

        virtual sal_Bool SAL_CALL convertFastPropertyValue(
                                    css::uno::Any & rConvertedValue,
                                    css::uno::Any & rOldValue,
                                    sal_Int32 nHandle,
                                    const css::uno::Any& rValue
                                )   throw (css::lang::IllegalArgumentException) override;

        virtual void SAL_CALL setFastPropertyValue_NoBroadcast(
                                    sal_Int32 nHandle,
                                    const css::uno::Any& rValue
                                )   throw (css::uno::Exception, std::exception) override;

        virtual void SAL_CALL getFastPropertyValue(
                                    css::uno::Any& rValue,
                                    sal_Int32 nHandle
                                ) const override;

        virtual void createStatement(JNIEnv* _pEnv) = 0;

        virtual ~java_sql_Statement_Base();

        sal_Int32 impl_getProperty(const char* _pMethodName, jmethodID& _inout_MethodID);
        sal_Int32 impl_getProperty(const char* _pMethodName, jmethodID& _inout_MethodID,sal_Int32 _nDefault);

    public:
        virtual jclass getMyClass() const override;

        // A ctor that is needed for returning the object
        java_sql_Statement_Base( JNIEnv * pEnv, java_sql_Connection& _rCon );

        sal_Int32   getStatementObjectID() const { return m_aLogger.getObjectID(); }

        // OComponentHelper
        virtual void SAL_CALL disposing() override;
        // XInterface
        virtual void SAL_CALL acquire() throw() override;
        virtual void SAL_CALL release() throw() override;
        virtual css::uno::Any SAL_CALL queryInterface( const css::uno::Type & rType ) throw(css::uno::RuntimeException, std::exception) override;
        //XTypeProvider
        virtual css::uno::Sequence< css::uno::Type > SAL_CALL getTypes(  ) throw(css::uno::RuntimeException, std::exception) override;

        // XPropertySet
        virtual css::uno::Reference< css::beans::XPropertySetInfo > SAL_CALL getPropertySetInfo(  ) throw(css::uno::RuntimeException, std::exception) override;
        // XStatement
        virtual css::uno::Reference< css::sdbc::XResultSet > SAL_CALL executeQuery( const OUString& sql ) throw(css::sdbc::SQLException, css::uno::RuntimeException, std::exception) override ;
        virtual sal_Int32 SAL_CALL executeUpdate( const OUString& sql ) throw(css::sdbc::SQLException, css::uno::RuntimeException, std::exception) override ;
        virtual sal_Bool SAL_CALL execute( const OUString& sql ) throw(css::sdbc::SQLException, css::uno::RuntimeException, std::exception) override ;
        virtual css::uno::Reference< css::sdbc::XConnection > SAL_CALL getConnection(  ) throw(css::sdbc::SQLException, css::uno::RuntimeException, std::exception) override ;
        // XWarningsSupplier
        virtual css::uno::Any SAL_CALL getWarnings(  ) throw(css::sdbc::SQLException, css::uno::RuntimeException, std::exception) override;
        virtual void SAL_CALL clearWarnings(  ) throw(css::sdbc::SQLException, css::uno::RuntimeException, std::exception) override;
        // XCancellable
        virtual void SAL_CALL cancel(  ) throw(css::uno::RuntimeException, std::exception) override;
        // XCloseable
        virtual void SAL_CALL close(  ) throw(css::sdbc::SQLException, css::uno::RuntimeException, std::exception) override;
        // XMultipleResults
        virtual css::uno::Reference< css::sdbc::XResultSet > SAL_CALL getResultSet(  ) throw(css::sdbc::SQLException, css::uno::RuntimeException, std::exception) override;
        virtual sal_Int32 SAL_CALL getUpdateCount(  ) throw(css::sdbc::SQLException, css::uno::RuntimeException, std::exception) override;
        virtual sal_Bool SAL_CALL getMoreResults(  ) throw(css::sdbc::SQLException, css::uno::RuntimeException, std::exception) override;
        //XGeneratedResultSet
        virtual css::uno::Reference< css::sdbc::XResultSet > SAL_CALL getGeneratedValues(  ) throw (css::sdbc::SQLException, css::uno::RuntimeException, std::exception) override;

    public:
        using ::cppu::OPropertySetHelper::getFastPropertyValue;
    };

    class OStatement_BASE2  :public java_sql_Statement_Base
                            ,public OSubComponent<OStatement_BASE2, java_sql_Statement_BASE>

    {
        friend class OSubComponent<OStatement_BASE2, java_sql_Statement_BASE>;
    public:
        OStatement_BASE2(JNIEnv * pEnv, java_sql_Connection& _rCon ) : java_sql_Statement_Base( pEnv, _rCon ),
                                OSubComponent<OStatement_BASE2, java_sql_Statement_BASE>(static_cast<cppu::OWeakObject*>(&_rCon), this){}

        // OComponentHelper
        virtual void SAL_CALL disposing() override;
        // XInterface
        virtual void SAL_CALL release() throw() override;
    };

    class java_sql_Statement :  public OStatement_BASE2,
                                public css::sdbc::XBatchExecution,
                                public css::lang::XServiceInfo
    {
    protected:
        // Static data for the class
        static jclass theClass;

        virtual void createStatement(JNIEnv* _pEnv) override;

        virtual ~java_sql_Statement();
    public:
        DECLARE_SERVICE_INFO();
        virtual jclass getMyClass() const override;

        // A ctor that is needed for returning the object
        java_sql_Statement( JNIEnv * pEnv, java_sql_Connection& _rCon ) : OStatement_BASE2( pEnv, _rCon){};

        virtual css::uno::Any SAL_CALL queryInterface( const css::uno::Type & rType ) throw(css::uno::RuntimeException, std::exception) override;
        virtual void SAL_CALL acquire() throw() override;
        virtual void SAL_CALL release() throw() override;
        // XBatchExecution
        virtual void SAL_CALL addBatch( const OUString& sql ) throw(css::sdbc::SQLException, css::uno::RuntimeException, std::exception) override;
        virtual void SAL_CALL clearBatch(  ) throw(css::sdbc::SQLException, css::uno::RuntimeException, std::exception) override;
        virtual css::uno::Sequence< sal_Int32 > SAL_CALL executeBatch(  ) throw(css::sdbc::SQLException, css::uno::RuntimeException, std::exception) override;
    };
}
#endif // INCLUDED_CONNECTIVITY_SOURCE_INC_JAVA_SQL_JSTATEMENT_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
