// Copyright 2021 DeoVolenteGames

#pragma once
/*
#include "CoreMinimal.h"
#include "NakamaBPExtension.h"
#include "NakamaProxy.h"
#include "NakamaCreateMatch.generated.h"

// USTRUCT(BlueprintType, Category = "Nakama BP Extension|Match")
// struct FNakamaMatchTicket {
// 	GENERATED_BODY()
//
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	FString Ticket;
//
// 	FNakamaMatchTicket() {}
// 	FNakamaMatchTicket(NAKAMA_NAMESPACE::NMatchTicket Ticket)
// 	{
// 		this.Ticket = FString(Ticket.ticket.c_str());
// 	}
// };

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnyCreateResponse, /*FNakamaMatchTicket* / FString, SuccessResponse, FNakamaErrorResponse, ErrorResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnSuccessCreateResponse, /*FNakamaMatchTicket* / FString, SuccessResponse);

/// https://heroiclabs.github.io/nakama-cpp/html/class_n_client_interface.html#a30824ec045d4308e13d34bc285311e2a
UCLASS()
class NAKAMABPEXTENSION_API UNakamaCreateMatch : public UOnlineBlueprintCallProxyBase,
	public TNakamaProxy</*FNakamaMatchTicket* / FString, FOnSuccessCreateResponse, FOnAnyCreateResponse>
{
	GENERATED_BODY()

public:
	void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", AutoCreateRefTerm = "StringProperties, NumericProperties, SuccessDelegate, ErrorDelegate"), Category = "Nakama BP Extension|Match")
		static UNakamaCreateMatch* CreateMatch(const int32 MinCount, const int32 MaxCount, const FString Query, const TMap<FString, FString> StringProperties, const TMap<FString, float> NumericProperties, const FOnSuccessCreateResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate);

private:
	UPROPERTY()
	int32 MinCount = 2;

	UPROPERTY()
	int32 MaxCount = 4;

	UPROPERTY()
	FString Query;

	UPROPERTY()
	TMap<FString, FString> StringProperties;

	UPROPERTY()
	TMap<FString, float> NumericProperties;

	UPROPERTY()
	FString Cursor;

	UPROPERTY(BlueprintAssignable)
	FOnAnyCreateResponse OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAnyCreateResponse OnError;
};
*/