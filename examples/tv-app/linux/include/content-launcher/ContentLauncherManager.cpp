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

#include "ContentLauncherManager.h"

using namespace std;
using namespace chip::app;
using namespace chip::app::Clusters;
using namespace chip::app::DataModel;
using namespace chip::app::Clusters::ContentLauncher;

ContentLauncherManager::ContentLauncherManager(list<std::string> acceptHeaderList, uint32_t supportedStreamingProtocols)
{
    mAcceptHeaderList            = acceptHeaderList;
    mSupportedStreamingProtocols = supportedStreamingProtocols;

    // Add dummy content for test cases
    ContentEntry entry1;
    entry1.mName = "TV Show Example";
    ParameterType parameter1;
    parameter1.type  = ParameterEnum::kActor;
    parameter1.value = chip::CharSpan::fromCharString("Gaby sHoffman");
    ParameterType parameter2;
    parameter2.type  = ParameterEnum::kChannel;
    parameter2.value = chip::CharSpan::fromCharString("PBS");
    ParameterType parameter3;
    parameter3.type  = ParameterEnum::kCharacter;
    parameter3.value = chip::CharSpan::fromCharString("Snow White");
    ParameterType parameter4;
    parameter4.type  = ParameterEnum::kDirector;
    parameter4.value = chip::CharSpan::fromCharString("Spike Lee");
    ParameterType parameter5;
    parameter5.type  = ParameterEnum::kFranchise;
    parameter5.value = chip::CharSpan::fromCharString("Star Wars");
    ParameterType parameter6;
    parameter6.type  = ParameterEnum::kGenre;
    parameter6.value = chip::CharSpan::fromCharString("Horror");
    ParameterType parameter7;
    parameter7.type  = ParameterEnum::kPopularity;
    parameter7.value = chip::CharSpan::fromCharString("Popularity");
    ParameterType parameter8;
    parameter8.type  = ParameterEnum::kProvider;
    parameter8.value = chip::CharSpan::fromCharString("Netflix");
    entry1.mSearchFields.push_back(parameter1);
    entry1.mSearchFields.push_back(parameter2);
    entry1.mSearchFields.push_back(parameter3);
    entry1.mSearchFields.push_back(parameter4);
    entry1.mSearchFields.push_back(parameter5);
    entry1.mSearchFields.push_back(parameter6);
    entry1.mSearchFields.push_back(parameter7);
    entry1.mSearchFields.push_back(parameter8);
    mContentList.push_back(entry1);

    ContentEntry entry2;
    entry2.mName = "Sports Example";
    ParameterType parameter21;
    parameter21.type  = ParameterEnum::kEvent;
    parameter21.value = chip::CharSpan::fromCharString("Football games");
    ParameterType parameter22;
    parameter22.type  = ParameterEnum::kLeague;
    parameter22.value = chip::CharSpan::fromCharString("NCAA");
    ParameterType parameter23;
    parameter23.type  = ParameterEnum::kSport;
    parameter23.value = chip::CharSpan::fromCharString("football");
    ParameterType parameter24;
    parameter24.type  = ParameterEnum::kSportsTeam;
    parameter24.value = chip::CharSpan::fromCharString("Arsenel");
    ParameterType parameter25;
    parameter25.type  = ParameterEnum::kType;
    parameter25.value = chip::CharSpan::fromCharString("TVSeries");
    entry2.mSearchFields.push_back(parameter21);
    entry2.mSearchFields.push_back(parameter22);
    entry2.mSearchFields.push_back(parameter23);
    entry2.mSearchFields.push_back(parameter24);
    entry2.mSearchFields.push_back(parameter25);
    mContentList.push_back(entry2);
}

void ContentLauncherManager::HandleLaunchContent(CommandResponseHelper<LaunchResponseType> & helper,
                                                 const DecodableList<ParameterType> & parameterList, bool autoplay,
                                                 const CharSpan & data)
{
    ChipLogProgress(Zcl, "ContentLauncherManager::HandleLaunchContent for endpoint %d", mEndpointId);
    string dataString(data.data(), data.size());

    ChipLogProgress(Zcl, "ContentLauncherManager::HandleLaunchUrl TEST CASE autoplay=%d data=%s ", (autoplay ? 1 : 0),
                    dataString.c_str());

    bool foundMatch = false;
    for (auto const & contentEntry : this->mContentList)
    {
        auto iter = parameterList.begin();
        while (iter.Next())
        {
            auto & parameterType = iter.GetValue();
            for (auto const & parameter : contentEntry.mSearchFields)
            {
                if (parameter.type == parameterType.type)
                {
                    string val1(parameter.value.data(), parameter.value.size());
                    string val2(parameterType.value.data(), parameterType.value.size());
                    if (strcmp(val1.c_str(), val2.c_str()) == 0)
                    {
                        ChipLogProgress(Zcl, " TEST CASE found match=%s type=%d", contentEntry.mName.c_str(),
                                        static_cast<uint16_t>(parameter.type));
                        foundMatch = true;
                    }
                }
            }
        }
    }

    if (!foundMatch)
    {
        ChipLogProgress(Zcl, " TEST CASE did not find a match");
    }

    LaunchResponseType response;
    // TODO: Insert code here
    response.data   = chip::MakeOptional(CharSpan::fromCharString("exampleData"));
    response.status = ContentLauncher::ContentLaunchStatusEnum::kSuccess;
    helper.Success(response);
}

void ContentLauncherManager::HandleLaunchUrl(CommandResponseHelper<LaunchResponseType> & helper, const CharSpan & contentUrl,
                                             const CharSpan & displayString, const BrandingInformationType & brandingInformation)
{
    ChipLogProgress(Zcl, "ContentLauncherManager::HandleLaunchUrl");

    string contentUrlString(contentUrl.data(), contentUrl.size());
    string displayStringString(displayString.data(), displayString.size());
    string providerNameString(brandingInformation.providerName.data(), brandingInformation.providerName.size());

    ChipLogProgress(
        Zcl, "ContentLauncherManager::HandleLaunchUrl TEST CASE ContentURL=%s DisplayString=%s BrandingInformation.ProviderName=%s",
        contentUrlString.c_str(), displayStringString.c_str(), providerNameString.c_str());

	//Code for Demo#1
	if (contentUrlString.find("https") != std::string::npos) {
		if(strcmp(displayStringString.c_str(), "demo") == 0)
		{
			string command("curl -H \"Authorization: Bearer `/usr/bin/WPEFrameworkSecurityUtility | cut -d'\"' -f 4`\" -d '{\"jsonrpc\": \"2.0\",\"id\": 42,\"method\": \"org.rdk.RDKShell.1.launch\",\"params\": {\"callsign\": \"demo\",\"type\": \"HtmlApp\",\"version\": \"1.0\",\"uri\":\"");
			command.append(contentUrlString);
			command.append("\",\"topmost\": true,\"focus\": true}}' http://127.0.0.1:9998/jsonrpc");
			ChipLogProgress(Zcl, "ContentLauncherManager::command = %s", command.c_str());
			system(command.c_str());
		}
		else if(strcmp(displayStringString.c_str(), "destroy") == 0)
		{
			string command("curl -H \"Authorization: Bearer `/usr/bin/WPEFrameworkSecurityUtility | cut -d'\"' -f 4`\" -d '{\"jsonrpc\":\"2.0\",\"id\":\"3\",\"method\": \"org.rdk.RDKShell.1.destroy\", \"params\": {\"callsign\": \"demo\"}}' http://127.0.0.1:9998/jsonrpc");
			ChipLogProgress(Zcl, "ContentLauncherManager::command = %s", command.c_str());
			system(command.c_str());
		}
	}
	//Code for Demo#2
	else
	{
		if(strcmp(contentUrlString.c_str(), "Netflix") == 0)
		{
			if(strcmp(displayStringString.c_str(), "demo") == 0)
			{
				string command("curl -H \"Authorization: Bearer `/usr/bin/WPEFrameworkSecurityUtility | cut -d'\"' -f 4`\" -d '{\"jsonrpc\": \"2.0\",\"id\": 42,\"method\": \"org.rdk.RDKShell.1.launch\",\"params\": {\"callsign\": \"Netflix-0\",\"type\": \"\",\"version\": \"1.0\",\"uri\":\"\",\"visible\": true,\"focused\": true,\"topmost\": true,\"focus\": true}}' http://127.0.0.1:9998/jsonrpc");
				system(command.c_str());
			}
			else if(strcmp(displayStringString.c_str(), "destroy") == 0)
			{
				string command("curl -H \"Authorization: Bearer `/usr/bin/WPEFrameworkSecurityUtility | cut -d'\"' -f 4`\" -d '{\"jsonrpc\":\"2.0\",\"id\":\"3\",\"method\": \"org.rdk.RDKShell.1.destroy\", \"params\": {\"callsign\": \"Netflix-0\"}}' http://127.0.0.1:9998/jsonrpc");
				system(command.c_str());
			}
		}
		else if(strcmp(contentUrlString.c_str(), "Disney") == 0)
		{
			if(strcmp(displayStringString.c_str(), "destroy") == 0)
			{
				string command("curl -H \"Authorization: Bearer `/usr/bin/WPEFrameworkSecurityUtility | cut -d'\"' -f 4`\" -d '{\"jsonrpc\":\"2.0\",\"id\":\"3\",\"method\": \"org.rdk.RDKShell.1.destroy\", \"params\": {\"callsign\": \"HtmlApp-0\"}}' http://127.0.0.1:9998/jsonrpc");
				system(command.c_str());
			}
			else
			{
				string command("curl -H \"Authorization: Bearer `/usr/bin/WPEFrameworkSecurityUtility | cut -d'\"' -f 4`\" -d '{\"jsonrpc\": \"2.0\",\"id\": 42,\"method\": \"org.rdk.RDKShell.1.launch\",\"params\": {\"callsign\": \"HtmlApp-0\",\"type\": \"\",\"version\": \"1.0\",\"uri\":\"");
				command.append(displayStringString);
				command.append("\",\"visible\": true,\"focused\": true,\"topmost\": true,\"focus\": true}}' http://127.0.0.1:9998/jsonrpc");
				system(command.c_str());
			}
		}
		else if(strcmp(contentUrlString.c_str(), "Prime") == 0)
		{
			if(strcmp(displayStringString.c_str(), "destroy") == 0)
			{
				string command("curl -H \"Authorization: Bearer `/usr/bin/WPEFrameworkSecurityUtility | cut -d'\"' -f 4`\" -d '{\"jsonrpc\":\"2.0\",\"id\":\"3\",\"method\": \"org.rdk.RDKShell.1.destroy\", \"params\": {\"callsign\": \"HtmlApp-0\"}}' http://127.0.0.1:9998/jsonrpc");
				system(command.c_str());
			}
			else
			{
				string command("curl -H \"Authorization: Bearer `/usr/bin/WPEFrameworkSecurityUtility | cut -d'\"' -f 4`\" -d '{\"jsonrpc\": \"2.0\",\"id\": 42,\"method\": \"org.rdk.RDKShell.1.launch\",\"params\": {\"callsign\": \"HtmlApp-0\",\"type\": \"\",\"version\": \"1.0\",\"uri\":\"");
				command.append(displayStringString);
				command.append("\",\"visible\": true,\"focused\": true,\"topmost\": true,\"focus\": true}}' http://127.0.0.1:9998/jsonrpc");
				system(command.c_str());
			}	
		}
		else if(strcmp(contentUrlString.c_str(), "YouTube") == 0)
		{
			if(strcmp(displayStringString.c_str(), "destroy") == 0)
			{
				string command("curl -H \"Authorization: Bearer `/usr/bin/WPEFrameworkSecurityUtility | cut -d'\"' -f 4`\" -d '{\"jsonrpc\":\"2.0\",\"id\":\"3\",\"method\": \"org.rdk.RDKShell.1.destroy\", \"params\": {\"callsign\": \"Cobalt-0\"}}' http://127.0.0.1:9998/jsonrpc");
				system(command.c_str());
			}
			else
			{
				//Launch
				string command("curl -H \"Authorization: Bearer `/usr/bin/WPEFrameworkSecurityUtility | cut -d'\"' -f 4`\" -d '{\"jsonrpc\": \"2.0\",\"id\": 42,\"method\": \"org.rdk.RDKShell.1.launch\",\"params\": {\"callsign\": \"Cobalt-0\",\"type\": \"Cobalt\",\"version\": \"1.0\",\"uri\":\"\",\"visible\": true,\"focused\": true,\"topmost\": true,\"focus\": true}}' http://127.0.0.1:9998/jsonrpc");

				//Adding deeplink command
				command.append(";");
				command.append("curl -H \"Authorization: Bearer `/usr/bin/WPEFrameworkSecurityUtility | cut -d'\"' -f 4`\" 'http://127.0.0.1:9998/jsonrpc' -d '{\"jsonrpc\": \"2.0\",\"id\": 4,\"method\": \"Cobalt-0.1.deeplink\", \"params\": {\"?launch=search&v=");
				command.append(displayStringString.c_str());
				command.append("&inApp=false\"}}' ; echo");
				
				ChipLogProgress(Zcl, "ContentLauncherManager::HandleLaunchUrl YouTube Command = %s", command.c_str());
				
				system(command.c_str());
			}
		}
	}

    // TODO: Insert code here
    LaunchResponseType response;
    response.data   = chip::MakeOptional(CharSpan::fromCharString("exampleData"));
    response.status = ContentLauncher::ContentLaunchStatusEnum::kSuccess;

    // Handle test cases
    if (contentUrlString == "https://badurl")
    {
        response.status = ContentLauncher::ContentLaunchStatusEnum::kUrlNotAvailable;
    }
    else if (contentUrlString == "https://csa-iot.org/badauth")
    {
        response.status = ContentLauncher::ContentLaunchStatusEnum::kAuthFailed;
    }

    helper.Success(response);
}

CHIP_ERROR ContentLauncherManager::HandleGetAcceptHeaderList(AttributeValueEncoder & aEncoder)
{
    ChipLogProgress(Zcl, "ContentLauncherManager::HandleGetAcceptHeaderList");
    return aEncoder.EncodeList([this](const auto & encoder) -> CHIP_ERROR {
        for (std::string & entry : mAcceptHeaderList)
        {
            CharSpan data = CharSpan::fromCharString(entry.c_str());
            ReturnErrorOnFailure(encoder.Encode(data));
        }
        return CHIP_NO_ERROR;
    });
}

uint32_t ContentLauncherManager::HandleGetSupportedStreamingProtocols()
{
    ChipLogProgress(Zcl, "ContentLauncherManager::HandleGetSupportedStreamingProtocols");
    return mSupportedStreamingProtocols;
}
