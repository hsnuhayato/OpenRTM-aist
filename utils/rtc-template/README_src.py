#!/usr/bin/env python
# -*- python -*-
#
#  @file README_src.py
#  @brief rtc-template RTComponent's README file generator class
#  @date $Date: 2007-01-11 07:47:03 $
#  @author Noriaki Ando <n-ando@aist.go.jp>
# 
#  Copyright (C) 2004-2005
#      Task-intelligence Research Group,
#      Intelligent Systems Research Institute,
#      National Institute of
#          Advanced Industrial Science and Technology (AIST), Japan
#      All rights reserved.
# 
#  $Id$
#

#
#  $Log: not supported by cvs2svn $
#  Revision 1.4  2005/09/08 09:23:36  n-ando
#  - A bug fix for merge function.
#
#  Revision 1.3  2005/09/06 14:36:53  n-ando
#  rtc-template's command options and data structure for ezt (Easy Template)
#  are changed for RTComponent's service features.
#  Now rtc-template can generate services' skeletons, stubs and
#  implementation files.
#  The implementation code generation uses omniidl's IDL parser.
#
#  Revision 1.2  2005/08/26 12:01:15  n-ando
#  Now rtc-template uses ezt (Easy Template).
#
#  Revision 1.1.1.1  2005/05/12 09:06:18  n-ando
#  Public release.
#
#

import re
import os
import time
import ezt
import gen_base

readme = """======================================================================
  RTComponent: [module.name] specificatioin

  OpenRTM-[version]
  Date: [date]

  This file is generated by rtc-template with the following argments.

[for fmtd_args]    [fmtd_args]
[end]
======================================================================
# <rtc-template block="module">
# </rtc-template>


======================================================================
    Activity definition
======================================================================

[b]Initializing[e]

[b]Ready[e]
	[b]Entry[e]
	[b]Do[e]
	[b]Exit[e]

[b]Starting[e]

[b]Active[e]
	[b]Entry[e]
	[b]Do[e]
	[b]Exit[e]

[b]Stopping[e]

[b]Error[e]
	[b]Entry[e]
	[b]Do[e]
	[b]Exit[e]


[b]Fatal Error[e]
	[b]Entry[e]
	[b]Do[e]
	[b]Exit[e]

[b]Exiting[e]

======================================================================
    InPorts definition
======================================================================
# <rtc-template block="inport">
# </rtc-template>

======================================================================
    OutPorts definition
======================================================================
# <rtc-template block="outport">
# </rtc-template>


======================================================================
    Service definition
======================================================================
# <rtc-template block="service">
# </rtc-template> 

======================================================================
    Configuration definition
======================================================================
This area is reserved for future OpenRTM.

"""

module = """Description: [module.desc]
Version:     [module.version]
Author:      [module.vendor]
Category:    [module.category]
Comp. Type:  [module.comp_type]
Act. Type:   [module.act_type]
MAX Inst.:   [module.max_inst]
Lang:        
Lang Type:   
"""

inport = """[for inport]
	Name:        [inport.name]
	PortNumber:  [inport.num]
	Description:
	PortType: 
	DataType:    [inport.type]
	MaxOut: 
	[b]Data Elements[e]
		Number:
		Name:
		Type:
		Unit:
		RangeLow:
		RangeHigh:
		DefaultValue:
[end]
"""

outport = """[for outport]
	Name:        [outport.name]
	PortNumber:  [outport.num]
	Description:
	PortType: 
	DataType:    [outport.type]
	MaxOut: 
	[b]Data Elements[e]
		Number:
		Name:
		Type:
		Unit:
		RangeLow:
		RangeHigh:
		DefaultValue:
[end]
"""
service = """[for service]
	Interface:   [service.type] 
	Name:        [service.name]
	Type:        [service.type]
[end]
"""

class README_src(gen_base.gen_base):
	def __init__(self, data):
		self.data = data.copy()
		self.data['fname'] = "README." + self.data['fname']
		self.data['version'] = os.popen("rtm-config --version", "r").read()
		self.data['date'] = time.asctime()
		self.data['b'] = "["
		self.data['e'] = "]"

		self.tags = {}
		self.tags["module"] = module
		self.tags["inport"] = inport
		self.tags["outport"] = outport
		self.tags["service"] = service

		self.gen_tags(self.tags)
		return

	def print_readme(self):
		self.gen(self.data["fname"], readme, self.data, self.tags)

	def print_all(self):
		self.print_readme()
	
