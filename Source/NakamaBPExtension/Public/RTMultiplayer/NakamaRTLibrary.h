// Copyright 2021 DeoVolenteGames

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "NakamaRTLibrary.generated.h"

UCLASS(meta=(Displayname="Nakama RT Multiplayer Library"))
class NAKAMABPEXTENSION_API UNakamaRTLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	public:
	// Remove a user from the matchmaker
	// https://heroiclabs.com/docs/nakama/concepts/matches/#remove-a-user-from-the-matchmaker
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Remove from Nakama Matchmaker"), Category = "Nakama BP Extension|RT Multiplayer")
	static void RemoveFromMatchmaker(const FString Ticket);

	// Connect the RT Client to the server. Needed before matchmaking or trying to connect to a match.
	// Returns true if the client was set up correctly, NOT if it is connected!
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Connect Nakama RT Client"), Category = "Nakama BP Extension|RT Multiplayer")
    static bool ConnectNakamaRTClient(const bool CreateStatus = true);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Leave Nakama Match"), Category = "Nakama BP Extension|RT Multiplayer")
	static void LeaveMatch(const FString MatchID);

	UFUNCTION(BlueprintCallable, Category = "Nakama BP Extension|RT Multiplayer")
    static void SendMatchData(const FString MatchID, const int OpCode, const FString Data);
};
