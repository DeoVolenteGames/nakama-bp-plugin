// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "../Public/RTMultiplayer/NakamaRTLibrary.h"
#include "NakamaBPExtension.h"

void UNakamaRTLibrary::RemoveFromMatchmaker(const FString Ticket)
{
	NakamaBP::RtClient->removeMatchmaker(TCHAR_TO_UTF8(*Ticket), []()
	{
	    // Don't know what to do here
	});
}

bool UNakamaRTLibrary::ConnectNakamaRTClient(const bool CreateStatus)
{
	if (NakamaBP::Session)
	{
		NakamaBP::RtClient->connect(NakamaBP::Session, CreateStatus);
		return true;
	}
	UE_LOG(LogTemp, Error, TEXT("NakamaBP::Session token invalid"));
	return false;
}

void UNakamaRTLibrary::LeaveMatch(const FString MatchID)
{
	NakamaBP::RtClient->leaveMatch(TCHAR_TO_UTF8(*MatchID));
}

void UNakamaRTLibrary::SendMatchData(const FString MatchID, const int OpCode, const FString Data)
{
	// TODO: Allow specifying presences
	NakamaBP::RtClient->sendMatchData(TCHAR_TO_UTF8(*MatchID), OpCode, TCHAR_TO_UTF8(*Data));
}

bool UNakamaRTLibrary::RTClientIsConnected()
{
	return NakamaBP::RtClient->isConnected();
}

void UNakamaRTLibrary::DisconnectRTClient()
{
	NakamaBP::RtClient->disconnect();
}