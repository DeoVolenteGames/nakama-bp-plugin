// Copyright 2021 DeoVolenteGames

#pragma once

#include "CoreMinimal.h"
#include "NakamaUnreal.h"
#include "NakamaRTTypes.generated.h"

USTRUCT(BlueprintType, Category = "Nakama BP Extension|RT Multiplayer")
struct NAKAMABPEXTENSION_API FNakamaUserPresence {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString UserId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SessionId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Username;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bPersistence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Status;

	FNakamaUserPresence() : bPersistence(false) {}
	FNakamaUserPresence(NAKAMA_NAMESPACE::NUserPresence UserPresence)
	{
		UserId = UserPresence.userId.c_str();             ///< The user this presence belongs to.
		SessionId = UserPresence.sessionId.c_str();          ///< A unique session ID identifying the particular connection, because the user may have many.
		Username = UserPresence.username.c_str();           ///< The username for display purposes.
		bPersistence = UserPresence.persistence;       ///< Whether this presence generates persistent data/messages, if applicable for the stream type.
		Status = UserPresence.status.c_str();  
	}
};

USTRUCT(BlueprintType, Category = "Nakama BP Extension|RT Multiplayer")
struct NAKAMABPEXTENSION_API FNakamaMatch {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString MatchId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bAuthoritative;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Label;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FNakamaUserPresence> Presences;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FNakamaUserPresence SelfPresence;

	FNakamaMatch() : bAuthoritative(false), Size(0) {}
	FNakamaMatch(NAKAMA_NAMESPACE::NMatch Match)
	{
		MatchId = Match.matchId.c_str();                     ///< The ID of the match, can be used to join.
		bAuthoritative = Match.authoritative;              ///< True if it's an server-managed authoritative match, false otherwise.
		Label = Match.label.c_str();                       ///< Match label, if any.
		Size = Match.size;                        ///< Current number of users in the match.
		Presences = NakamaBP::MakeArray<FNakamaUserPresence>(Match.presences);    ///< The users currently in the match.
		SelfPresence = Match.self;                      ///< A reference to the current user's presence in the match.
	}
};