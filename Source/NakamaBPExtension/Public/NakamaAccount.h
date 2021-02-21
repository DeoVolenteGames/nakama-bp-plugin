// Copyright 2021 DeoVolenteGames

#pragma once

#include "CoreMinimal.h"
#include "NakamaBPExtension.h"
#include "NakamaProxy.h"
#include "NakamaAccount.generated.h"

// TODO: Add the missing data.
// TODO: Consider making this just a plain account struct. Could have this only contain account and getters? That seems bad though.
// TODO: I definitely need a way to access User data as struct separately.
USTRUCT(BlueprintType)
struct FNakamaAccountResponse {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Username;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Online;

	FNakamaAccountResponse(const NAKAMA_NAMESPACE::NAccount& Account)
	{
		ID = FString(Account.user.id.c_str());
		Username = FString(Account.user.username.c_str());
		DisplayName = FString(Account.user.displayName.c_str());
		Online = Account.user.online;
	}
	// UE4 is freaking out about the naked constructor 
	FNakamaAccountResponse() {}//: ID(""), Username(""), DisplayName(""), Online("") {}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnyAccountResponse, FNakamaAccountResponse, SuccessResponse, FNakamaErrorResponse, ErrorResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnAccountSuccessResponse, FNakamaAccountResponse, SuccessResponse);

/**
 * Get Account function.
 * https://heroiclabs.com/docs/user-accounts/
 */
UCLASS()
class NAKAMABPEXTENSION_API UNakamaAccount : public UOnlineBlueprintCallProxyBase, 
	public TNakamaProxy<FNakamaAccountResponse, FOnAccountSuccessResponse, FOnAnyAccountResponse>
{
	GENERATED_BODY()

public:
	// Generate a delegate for the OnGetResult event

	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", AutoCreateRefTerm = "SuccessDelegate, ErrorDelegate"), Category = "Nakama BP Extension")
	static UNakamaAccount* GetAccount(const FOnAccountSuccessResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate);

private:

	UPROPERTY()
	FString RpcID;

	UPROPERTY()
	FString Payload;

	UPROPERTY(BlueprintAssignable)
	FOnAnyAccountResponse OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAnyAccountResponse OnError;
};
