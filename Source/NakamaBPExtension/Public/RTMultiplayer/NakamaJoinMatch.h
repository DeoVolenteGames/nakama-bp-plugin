// Copyright 2021 DeoVolenteGames

#pragma once

#include "CoreMinimal.h"
#include "NakamaBPExtension.h"
#include "NakamaProxy.h"
#include "NakamaRTTypes.h"
#include "NakamaJoinMatch.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnyJoinResponse, FNakamaMatch, SuccessResponse, FNakamaErrorResponse, ErrorResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSuccessJoinResponse, FNakamaMatch, SuccessResponse);

/// https://heroiclabs.github.io/nakama-cpp/html/class_n_client_interface.html#a30824ec045d4308e13d34bc285311e2a
UCLASS()
class NAKAMABPEXTENSION_API UNakamaJoinMatch : public UOnlineBlueprintCallProxyBase,
	public TNakamaProxy<FNakamaMatch, FOnSuccessJoinResponse, FOnAnyJoinResponse>
{
	GENERATED_BODY()

public:
	void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", AutoCreateRefTerm = "StringProperties, SuccessDelegate, ErrorDelegate"), Category = "Nakama BP Extension|Match")
		static UNakamaJoinMatch* JoinMatch(const FString MatchID, const TMap<FString, FString> Metadata, const FOnSuccessJoinResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate);

private:
	UPROPERTY()
	FString MatchID;

	UPROPERTY()
	TMap<FString, FString> Metadata;

	UPROPERTY(BlueprintAssignable)
	FOnAnyJoinResponse OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAnyJoinResponse OnError;
};
