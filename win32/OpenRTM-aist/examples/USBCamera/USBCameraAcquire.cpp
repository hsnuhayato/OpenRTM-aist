// -*- C++ -*-
/*!
 * @file  USBCameraAcquire.cpp
 * @brief USB Camera Acquire component
 * $Date: 2007-07-20 20:33:18 $
 *
 * $Id: USBCameraAcquire.cpp,v 1.1.2.1 2007-07-20 20:33:18 n-ando Exp $
 */

#include "USBCameraAcquire.h"
#include <iostream>
using namespace std;

// Module specification
// <rtc-template block="module_spec">
static const char* usbcameraacquire_spec[] =
  {
    "implementation_id", "USBCameraAcquire",
    "type_name",         "USBCameraAcquire",
    "description",       "USB Camera Acquire component",
    "version",           "1.0",
    "vendor",            "Noriaki Ando, AIST",
    "category",          "example",
    "activity_type",     "DataFlowComponent",
    "max_instance",      "10",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

USBCameraAcquire::USBCameraAcquire(RTC::Manager* manager)
  : RTC::DataFlowComponentBase(manager),
    // <rtc-template block="initializer">
    m_outOut("out", m_out),
    // </rtc-template>
	dummy(0)
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  registerOutPort("out", m_outOut);
  //registerOutPort("OutPortPicture", mOutPortPicture);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

}

USBCameraAcquire::~USBCameraAcquire()
{
}
/*
RTC::ReturnCode_t USBCameraAcquire::onInitialize()
{

  return RTC::RTC_OK;
}
*/

RTC::ReturnCode_t USBCameraAcquire::onFinalize()
{	
	return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t USBCameraAcquire::onStartup(RTC::UniqueId ec_id)
{

}
*/

/*
RTC::ReturnCode_t USBCameraAcquire::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::OK;
}
*/

RTC::ReturnCode_t USBCameraAcquire::onActivated(RTC::UniqueId ec_id)
{
	//カメラデバイスの探索
	if(NULL==(m_capture = cvCreateCameraCapture(CV_CAP_ANY))){
		cout<<"カメラがみつかりません"<<endl;
		return RTC::RTC_ERROR;
	}
	return RTC::RTC_OK;
}



RTC::ReturnCode_t USBCameraAcquire::onDeactivated(RTC::UniqueId ec_id)
{
	//カメラ用メモリの解放
	cvReleaseCapture(&m_capture);
	return RTC::RTC_OK;
}



RTC::ReturnCode_t USBCameraAcquire::onExecute(RTC::UniqueId ec_id)
{
	static ACE_Time_Value tm_pre;
	static int count = 0;
//		IplImage* src = NULL;	//カメラの画像を格納するためのメモリ
	                        //処理や解放をおこなってはならない（マニュアルによると）
		IplImage* cam_frame = NULL; //  = cvQueryFrame(m_capture);

		//キャプチャ側から画像を取り出す
		cam_frame = cvQueryFrame(m_capture);
		if(NULL == cam_frame)
		  {
			std::cout << "画像がキャプチャできません!!" << std::endl;
			return RTC::RTC_ERROR;
		  }

		IplImage* frame = cvCreateImage(cvGetSize(cam_frame), 8, 3);

		if(cam_frame ->origin == IPL_ORIGIN_TL)
            cvCopy(cam_frame, frame);
        else
            cvFlip(cam_frame, frame);


		//std::cout << "src->nChannels :" << src->nChannels << std::endl;
		//std::cout << "src->width :" << src->width << std::endl;
		//std::cout << "src->height :" << src->height << std::endl;
	int len = frame->nChannels * frame->width * frame->height;

	m_out.data.length(len);
	//	for(int i=0; i<len; i++)
	//	{
	//		m_out.data[i] = src->imageData[i];
	//	}
	memcpy((void *)&(m_out.data[0]),frame->imageData,len);

  m_outOut.write();

	if (count > 120)
	{
		count = 0;
		ACE_Time_Value tm;
		tm = ACE_OS::gettimeofday();
		std::cout << 120*1000/(tm - tm_pre).msec() << " [FPS]" << std::endl;
		tm_pre = tm;
	}
	++count;

  return RTC::RTC_OK;
}


/*
RTC::ReturnCode_t USBCameraAcquire::onAborting(RTC::UniqueId ec_id)
{

  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t USBCameraAcquire::onError(RTC::UniqueId ec_id)
{
  return RTC::OK;
}
*/

/*
RTC::ReturnCode_t USBCameraAcquire::onReset(RTC::UniqueId ec_id)
{
  return RTC::OK;
}
*/

/*
RTC::ReturnCode_t USBCameraAcquire::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::OK;
}
*/

/*
RTC::ReturnCode_t USBCameraAcquire::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::OK;
}
*/



extern "C"
{
 
  void USBCameraAcquireInit(RTC::Manager* manager)
  {
    RTC::Properties profile(usbcameraacquire_spec);
    manager->registerFactory(profile,
                             RTC::Create<USBCameraAcquire>,
                             RTC::Delete<USBCameraAcquire>);
  }
  
};


