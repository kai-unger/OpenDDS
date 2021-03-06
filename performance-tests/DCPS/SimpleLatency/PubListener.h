// -*- C++ -*-
//
#ifndef DATAREADER_LISTENER_IMPL
#define DATAREADER_LISTENER_IMPL

#include <dds/DdsDcpsSubscriptionC.h>
#include <dds/DdsDcpsPublicationC.h>
#include "ace/High_Res_Timer.h"
#include "DDSPerfTestTypeSupportImpl.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

//Class AckDataReaderListenerImpl
class AckDataReaderListenerImpl
  : public virtual OpenDDS::DCPS::LocalObject<DDS::DataReaderListener>
{
public:
  //Constructor
  AckDataReaderListenerImpl (CORBA::Long size);

  void init (DDS::DataReader_ptr dr, DDS::DataWriter_ptr dw, bool use_zero_copy_read);
  //Destructor
  virtual ~AckDataReaderListenerImpl (void);

  virtual void on_requested_deadline_missed (
    DDS::DataReader_ptr reader,
    const DDS::RequestedDeadlineMissedStatus & status)
    throw (CORBA::SystemException);

  virtual void on_requested_incompatible_qos (
    DDS::DataReader_ptr reader,
    const DDS::RequestedIncompatibleQosStatus & status)
  throw (CORBA::SystemException);

  virtual void on_liveliness_changed (
    DDS::DataReader_ptr reader,
    const DDS::LivelinessChangedStatus & status)
  throw (CORBA::SystemException);

  virtual void on_subscription_matched (
    DDS::DataReader_ptr reader,
    const DDS::SubscriptionMatchedStatus & status
  )
  throw (CORBA::SystemException);

  virtual void on_sample_rejected(
    DDS::DataReader_ptr reader,
    const DDS::SampleRejectedStatus& status
  )
  throw (CORBA::SystemException);

  virtual void on_data_available(
    DDS::DataReader_ptr reader
  )
  throw (CORBA::SystemException);

  virtual void on_sample_lost(
    DDS::DataReader_ptr reader,
    const DDS::SampleLostStatus& status
  )
  throw (CORBA::SystemException);

  int done() const {
    return this->done_;
  }

private:

  DDS::DataWriter_var writer_;
  DDS::DataReader_var reader_;
  DDSPerfTest::AckMessageDataReaderImpl* dr_servant_;
  DDSPerfTest::PubMessageDataWriterImpl* dw_servant_;
  DDS::InstanceHandle_t handle_;
  CORBA::Long sample_num_;
  int   done_;
  ACE_High_Res_Timer timer_;
  bool  use_zero_copy_;
};

#endif /* DATAREADER_LISTENER_IMPL  */
