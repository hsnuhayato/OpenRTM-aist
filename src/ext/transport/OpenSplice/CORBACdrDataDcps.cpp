//******************************************************************
// 
//  Generated by IDL to C++ Translator
//  
//  File name: CORBACdrDataDcps.cpp
//  Source: CORBACdrDataDcps.idl
//  Generated: Wed Mar 27 20:28:43 2019
//  OpenSplice 6.9.190227OSS
//  
//******************************************************************

#include "CORBACdrDataDcps.h"
#include <iostream>

#if DDS_USE_EXPLICIT_TEMPLATES
template class DDS_DCPSUVLSeq < OpenRTM::CORBACdrData, struct CORBACdrDataSeq_uniq_>;
#endif

const char * OpenRTM::CORBACdrDataTypeSupportInterface::_local_id = "IDL:OpenRTM/CORBACdrDataTypeSupportInterface:1.0";

OpenRTM::CORBACdrDataTypeSupportInterface_ptr OpenRTM::CORBACdrDataTypeSupportInterface::_duplicate (OpenRTM::CORBACdrDataTypeSupportInterface_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean OpenRTM::CORBACdrDataTypeSupportInterface::_local_is_a (const char * _id)
{
   if (strcmp (_id, OpenRTM::CORBACdrDataTypeSupportInterface::_local_id) == 0)
   {
      return true;
   }

   typedef DDS::TypeSupport NestedBase_1;

   if (NestedBase_1::_local_is_a (_id))
   {
      return true;
   }

   return false;
}

OpenRTM::CORBACdrDataTypeSupportInterface_ptr OpenRTM::CORBACdrDataTypeSupportInterface::_narrow (DDS::Object_ptr p)
{
   OpenRTM::CORBACdrDataTypeSupportInterface_ptr result = nullptr;
   if (p && p->_is_a (OpenRTM::CORBACdrDataTypeSupportInterface::_local_id))
   {
      result = dynamic_cast < OpenRTM::CORBACdrDataTypeSupportInterface_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

OpenRTM::CORBACdrDataTypeSupportInterface_ptr OpenRTM::CORBACdrDataTypeSupportInterface::_unchecked_narrow (DDS::Object_ptr p)
{
   OpenRTM::CORBACdrDataTypeSupportInterface_ptr result;
   result = dynamic_cast < OpenRTM::CORBACdrDataTypeSupportInterface_ptr> (p);
   if (result) result->m_count++;
   return result;
}

const char * OpenRTM::CORBACdrDataDataWriter::_local_id = "IDL:OpenRTM/CORBACdrDataDataWriter:1.0";

OpenRTM::CORBACdrDataDataWriter_ptr OpenRTM::CORBACdrDataDataWriter::_duplicate (OpenRTM::CORBACdrDataDataWriter_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean OpenRTM::CORBACdrDataDataWriter::_local_is_a (const char * _id)
{
   if (strcmp (_id, OpenRTM::CORBACdrDataDataWriter::_local_id) == 0)
   {
      return true;
   }

   typedef DDS::DataWriter NestedBase_1;

   if (NestedBase_1::_local_is_a (_id))
   {
      return true;
   }

   return false;
}

OpenRTM::CORBACdrDataDataWriter_ptr OpenRTM::CORBACdrDataDataWriter::_narrow (DDS::Object_ptr p)
{
   OpenRTM::CORBACdrDataDataWriter_ptr result = nullptr;
   if (p && p->_is_a (OpenRTM::CORBACdrDataDataWriter::_local_id))
   {
      result = dynamic_cast < OpenRTM::CORBACdrDataDataWriter_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

OpenRTM::CORBACdrDataDataWriter_ptr OpenRTM::CORBACdrDataDataWriter::_unchecked_narrow (DDS::Object_ptr p)
{
   OpenRTM::CORBACdrDataDataWriter_ptr result;
   result = dynamic_cast < OpenRTM::CORBACdrDataDataWriter_ptr> (p);
   if (result) result->m_count++;
   return result;
}

const char * OpenRTM::CORBACdrDataDataReader::_local_id = "IDL:OpenRTM/CORBACdrDataDataReader:1.0";

OpenRTM::CORBACdrDataDataReader_ptr OpenRTM::CORBACdrDataDataReader::_duplicate (OpenRTM::CORBACdrDataDataReader_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean OpenRTM::CORBACdrDataDataReader::_local_is_a (const char * _id)
{
   if (strcmp (_id, OpenRTM::CORBACdrDataDataReader::_local_id) == 0)
   {
      return true;
   }

   typedef DDS::DataReader NestedBase_1;

   if (NestedBase_1::_local_is_a (_id))
   {
      return true;
   }

   return false;
}

OpenRTM::CORBACdrDataDataReader_ptr OpenRTM::CORBACdrDataDataReader::_narrow (DDS::Object_ptr p)
{
   OpenRTM::CORBACdrDataDataReader_ptr result = nullptr;
   if (p && p->_is_a (OpenRTM::CORBACdrDataDataReader::_local_id))
   {
      result = dynamic_cast < OpenRTM::CORBACdrDataDataReader_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

OpenRTM::CORBACdrDataDataReader_ptr OpenRTM::CORBACdrDataDataReader::_unchecked_narrow (DDS::Object_ptr p)
{
   OpenRTM::CORBACdrDataDataReader_ptr result;
   result = dynamic_cast < OpenRTM::CORBACdrDataDataReader_ptr> (p);
   if (result) result->m_count++;
   return result;
}

const char * OpenRTM::CORBACdrDataDataReaderView::_local_id = "IDL:OpenRTM/CORBACdrDataDataReaderView:1.0";

OpenRTM::CORBACdrDataDataReaderView_ptr OpenRTM::CORBACdrDataDataReaderView::_duplicate (OpenRTM::CORBACdrDataDataReaderView_ptr p)
{
   if (p) p->m_count++;
   return p;
}

DDS::Boolean OpenRTM::CORBACdrDataDataReaderView::_local_is_a (const char * _id)
{
   if (strcmp (_id, OpenRTM::CORBACdrDataDataReaderView::_local_id) == 0)
   {
      return true;
   }

   typedef DDS::DataReaderView NestedBase_1;

   if (NestedBase_1::_local_is_a (_id))
   {
      return true;
   }

   return false;
}

OpenRTM::CORBACdrDataDataReaderView_ptr OpenRTM::CORBACdrDataDataReaderView::_narrow (DDS::Object_ptr p)
{
   OpenRTM::CORBACdrDataDataReaderView_ptr result = nullptr;
   if (p && p->_is_a (OpenRTM::CORBACdrDataDataReaderView::_local_id))
   {
      result = dynamic_cast < OpenRTM::CORBACdrDataDataReaderView_ptr> (p);
      if (result) result->m_count++;
   }
   return result;
}

OpenRTM::CORBACdrDataDataReaderView_ptr OpenRTM::CORBACdrDataDataReaderView::_unchecked_narrow (DDS::Object_ptr p)
{
   OpenRTM::CORBACdrDataDataReaderView_ptr result;
   result = dynamic_cast < OpenRTM::CORBACdrDataDataReaderView_ptr> (p);
   if (result) result->m_count++;
   return result;
}


