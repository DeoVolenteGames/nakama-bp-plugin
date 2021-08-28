// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "NakamaBPExtensionLibrary.h"
#include "NakamaBPExtension.h"

void UNakamaBPExtensionLibrary::CreateClient(const FString ServerKey, const FString Host, const int Port)
{
	// https://heroiclabs.com/docs/unreal-client-guide/

	// Quickly setup a client for a local server.
	NAKAMA_NAMESPACE::NClientParameters parameters = NAKAMA_NAMESPACE::NClientParameters();

	if (!ServerKey.IsEmpty())
		parameters.serverKey = TCHAR_TO_UTF8(*ServerKey);

	if (!Host.IsEmpty())
		parameters.host = TCHAR_TO_UTF8(*Host);

	if (Port >= 0)
		parameters.port = Port;

	NakamaBP::Client = NAKAMA_NAMESPACE::createDefaultClient(parameters);

	UE_LOG(LogTemp, Log, TEXT("Connection settings - key: %s, host: %s, port: %d"), UTF8_TO_TCHAR(parameters.serverKey.c_str()), UTF8_TO_TCHAR(parameters.host.c_str()), (int)parameters.port);
}

bool UNakamaBPExtensionLibrary::GetSessionKey(FString & Token)
{
	if (NakamaBP::Session)
	{
		Token = FString(NakamaBP::Session->getAuthToken().c_str());
		return true;
	}
	return false;
}

void UNakamaBPExtensionLibrary::DisconnectClient()
{
	NakamaBP::Client->disconnect();
}
