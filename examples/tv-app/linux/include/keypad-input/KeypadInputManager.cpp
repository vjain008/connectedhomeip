/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include "KeypadInputManager.h"

using namespace std;
using namespace chip;
using namespace chip::app::Clusters::KeypadInput;

void KeypadInputManager::HandleSendKey(CommandResponseHelper<SendKeyResponseType> & helper, const CecKeyCodeType & keycCode)
{
    // TODO: Insert code here
    Commands::SendKeyResponse::Type response;

    switch (keycCode)
    {
    case CecKeyCodeType::kUp:
        {
			string command("curl -H \"Authorization: Bearer `/usr/bin/WPEFrameworkSecurityUtility | cut -d'\"' -f 4`\" -d '{\"jsonrpc\":\"2.0\",\"id\":\"3\",\"method\": \"org.rdk.RDKShell.1.generateKey\",\"params\":{\"keys\":[{\"keyCode\":38}]}}' http://127.0.0.1:9998/jsonrpc");
			system(command.c_str());
			response.status = chip::app::Clusters::KeypadInput::KeypadInputStatusEnum::kSuccess;
		}
        break;
    case CecKeyCodeType::kDown:
        {
			string command("curl -H \"Authorization: Bearer `/usr/bin/WPEFrameworkSecurityUtility | cut -d'\"' -f 4`\" -d '{\"jsonrpc\":\"2.0\",\"id\":\"3\",\"method\": \"org.rdk.RDKShell.1.generateKey\",\"params\":{\"keys\":[{\"keyCode\":40}]}}' http://127.0.0.1:9998/jsonrpc");
			system(command.c_str());
			response.status = chip::app::Clusters::KeypadInput::KeypadInputStatusEnum::kSuccess;
		}
        break;
    case CecKeyCodeType::kLeft:
        {
			string command("curl -H \"Authorization: Bearer `/usr/bin/WPEFrameworkSecurityUtility | cut -d'\"' -f 4`\" -d '{\"jsonrpc\":\"2.0\",\"id\":\"3\",\"method\": \"org.rdk.RDKShell.1.generateKey\",\"params\":{\"keys\":[{\"keyCode\":37}]}}' http://127.0.0.1:9998/jsonrpc");
			system(command.c_str());
			response.status = chip::app::Clusters::KeypadInput::KeypadInputStatusEnum::kSuccess;
		}
        break;
    case CecKeyCodeType::kRight:
        {
			string command("curl -H \"Authorization: Bearer `/usr/bin/WPEFrameworkSecurityUtility | cut -d'\"' -f 4`\" -d '{\"jsonrpc\":\"2.0\",\"id\":\"3\",\"method\": \"org.rdk.RDKShell.1.generateKey\",\"params\":{\"keys\":[{\"keyCode\":39}]}}' http://127.0.0.1:9998/jsonrpc");
			system(command.c_str());
			response.status = chip::app::Clusters::KeypadInput::KeypadInputStatusEnum::kSuccess;
		}
        break;
    case CecKeyCodeType::kSelect:
		{
			string command("curl -H \"Authorization: Bearer `/usr/bin/WPEFrameworkSecurityUtility | cut -d'\"' -f 4`\" -d '{\"jsonrpc\":\"2.0\",\"id\":\"3\",\"method\": \"org.rdk.RDKShell.1.generateKey\",\"params\":{\"keys\":[{\"keyCode\":13}]}}' http://127.0.0.1:9998/jsonrpc");
			system(command.c_str());
			response.status = chip::app::Clusters::KeypadInput::KeypadInputStatusEnum::kSuccess;
		}
        break;
    case CecKeyCodeType::kBackward:
        {
			string command("curl -H \"Authorization: Bearer `/usr/bin/WPEFrameworkSecurityUtility | cut -d'\"' -f 4`\" -d '{\"jsonrpc\":\"2.0\",\"id\":\"3\",\"method\": \"org.rdk.RDKShell.1.generateKey\",\"params\":{\"keys\":[{\"keyCode\":8}]}}' http://127.0.0.1:9998/jsonrpc");
			system(command.c_str());
			response.status = chip::app::Clusters::KeypadInput::KeypadInputStatusEnum::kSuccess;
		}
        break;
    case CecKeyCodeType::kExit:
        response.status = chip::app::Clusters::KeypadInput::KeypadInputStatusEnum::kSuccess;
        break;
    case CecKeyCodeType::kRootMenu:
        response.status = chip::app::Clusters::KeypadInput::KeypadInputStatusEnum::kSuccess;
        break;
    case CecKeyCodeType::kSetupMenu:
        {
			string command("curl -H \"Authorization: Bearer `/usr/bin/WPEFrameworkSecurityUtility | cut -d'\"' -f 4`\" -d '{\"jsonrpc\":\"2.0\",\"id\":\"3\",\"method\": \"org.rdk.RDKShell.1.generateKey\",\"params\":{\"keys\":[{\"keyCode\":113}]}}' http://127.0.0.1:9998/jsonrpc");
			system(command.c_str());
			response.status = chip::app::Clusters::KeypadInput::KeypadInputStatusEnum::kSuccess;
		}
        break;
    case CecKeyCodeType::kEnter:
        {
			string command("curl -H \"Authorization: Bearer `/usr/bin/WPEFrameworkSecurityUtility | cut -d'\"' -f 4`\" -d '{\"jsonrpc\":\"2.0\",\"id\":\"3\",\"method\": \"org.rdk.RDKShell.1.generateKey\",\"params\":{\"keys\":[{\"keyCode\":13}]}}' http://127.0.0.1:9998/jsonrpc");
			system(command.c_str());
			response.status = chip::app::Clusters::KeypadInput::KeypadInputStatusEnum::kSuccess;
		}
        break;
    case CecKeyCodeType::kNumber0OrNumber10:
        response.status = chip::app::Clusters::KeypadInput::KeypadInputStatusEnum::kSuccess;
        break;
    case CecKeyCodeType::kNumbers1:
        response.status = chip::app::Clusters::KeypadInput::KeypadInputStatusEnum::kSuccess;
        break;
    case CecKeyCodeType::kNumbers2:
        response.status = chip::app::Clusters::KeypadInput::KeypadInputStatusEnum::kSuccess;
        break;
    case CecKeyCodeType::kNumbers3:
        response.status = chip::app::Clusters::KeypadInput::KeypadInputStatusEnum::kSuccess;
        break;
    case CecKeyCodeType::kNumbers4:
        response.status = chip::app::Clusters::KeypadInput::KeypadInputStatusEnum::kSuccess;
        break;
    case CecKeyCodeType::kNumbers5:
        response.status = chip::app::Clusters::KeypadInput::KeypadInputStatusEnum::kSuccess;
        break;
    case CecKeyCodeType::kNumbers6:
        response.status = chip::app::Clusters::KeypadInput::KeypadInputStatusEnum::kSuccess;
        break;
    case CecKeyCodeType::kNumbers7:
        response.status = chip::app::Clusters::KeypadInput::KeypadInputStatusEnum::kSuccess;
        break;
    case CecKeyCodeType::kNumbers8:
        response.status = chip::app::Clusters::KeypadInput::KeypadInputStatusEnum::kSuccess;
        break;
    case CecKeyCodeType::kNumbers9:
        response.status = chip::app::Clusters::KeypadInput::KeypadInputStatusEnum::kSuccess;
        break;
    default:
        response.status = chip::app::Clusters::KeypadInput::KeypadInputStatusEnum::kUnsupportedKey;
    }

    helper.Success(response);
}
