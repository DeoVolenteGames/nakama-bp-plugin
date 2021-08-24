// Copyright 2021 DeoVolenteGames

#pragma once

#include "CoreMinimal.h"
#include "NakamaBPExtension.h"
#include "NakamaProxy.h"
#include "NakamaJoinMatchmaker.generated.h"

USTRUCT(BlueprintType, Category = "Nakama BP Extension|RT Multiplayer")
struct NAKAMABPEXTENSION_API FNakamaMatchRequest {
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MinCount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MaxCount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Query;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FString, FString> StringProperties;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FString, float> NumericProperties;

	FNakamaMatchRequest() : MinCount(2), MaxCount(4), Query(TEXT("*")) {}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnyJoinMatchmakerResponse, FString, MatchmakingTicket, FNakamaErrorResponse, ErrorResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSuccessJoinMatchmakerResponse, FString, MatchmakingTicket);

/// https://heroiclabs.github.io/nakama-cpp/html/class_n_client_interface.html#a30824ec045d4308e13d34bc285311e2a
UCLASS()
class NAKAMABPEXTENSION_API UNakamaJoinMatchmaker : public UOnlineBlueprintCallProxyBase,
	public TNakamaProxy<FString, FOnSuccessJoinMatchmakerResponse, FOnAnyJoinMatchmakerResponse>
{
	GENERATED_BODY()

public:
	void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", AutoCreateRefTerm = "StringProperties, NumericProperties, SuccessDelegate, ErrorDelegate"), Category = "Nakama BP Extension|Matchmaker")
		static UNakamaJoinMatchmaker* JoinMatchmaker(const FNakamaMatchRequest MatchRequest, const FOnSuccessJoinMatchmakerResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate);

private:
	UPROPERTY()
	FNakamaMatchRequest MatchmakingRequest;

	UPROPERTY(BlueprintAssignable)
	FOnAnyJoinMatchmakerResponse OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAnyJoinMatchmakerResponse OnError;
};
