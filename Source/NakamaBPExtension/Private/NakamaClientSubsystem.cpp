// Copyright 2021 DeoVolenteGames


#include "NakamaClientSubsystem.h"
#include "NakamaBPExtension.h"

void UNakamaClientSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	RtListener = NAKAMA_NAMESPACE::NRtDefaultClientListener();

	RtListener.setMatchmakerMatchedCallback([this](const NAKAMA_NAMESPACE::NMatchmakerMatchedPtr Matched)
    {
		OnMatchedResponse.Broadcast(Matched->ticket.c_str(), Matched->matchId.c_str());

		NakamaBP::RtClient->joinMatchByToken(Matched->token, [this](const NAKAMA_NAMESPACE::NMatch& Match)
        {
            OnJoinedResponse.Broadcast(Match);
        });
    });

	RtListener.setMatchPresenceCallback([this](const NAKAMA_NAMESPACE::NMatchPresenceEvent& Event)
	{
		for (auto& Presence : Event.joins)
		{
			OnUserJoined.Broadcast(Presence);
		}

		for (auto& Presence : Event.leaves)
		{
			OnUserLeft.Broadcast(Presence);
		}
	});

	RtListener.setMatchDataCallback([this](const NAKAMA_NAMESPACE::NMatchData& MatchData)
	{
		OnMatchDataReceived.Broadcast(MatchData.matchId.c_str(), MatchData.opCode, MatchData.data.c_str());
	});

	RtListener.setConnectCallback([this]()
	{
	    UE_LOG(LogTemp, Warning, TEXT("Socket connected"));

		OnConnected.Broadcast();
	});
	
	NakamaBP::RtClient->setListener(&RtListener);
}

void UNakamaClientSubsystem::Deinitialize()
{
	// Clean up anything we need to clean up
}
