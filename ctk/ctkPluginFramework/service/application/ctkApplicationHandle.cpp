/*=============================================================================

  Library: CTK

  Copyright (c) German Cancer Research Center,
    Division of Medical and Biological Informatics

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/

#include "ctkApplicationHandle.h"

#include <ctkPluginConstants.h>

const QString ctkApplicationHandle::APPLICATION_PID = "service.pid"; //ctkPluginConstants::SERVICE_PID;
const QString ctkApplicationHandle::APPLICATION_DESCRIPTOR = "application.descriptor";
const QString ctkApplicationHandle::APPLICATION_STATE = "application.state";
const QString ctkApplicationHandle::APPLICATION_SUPPORTS_EXITVALUE = "application.supports.exitvalue";

const QString ctkApplicationHandle::RUNNING = "RUNNING";
const QString ctkApplicationHandle::STOPPING = "STOPPING";
