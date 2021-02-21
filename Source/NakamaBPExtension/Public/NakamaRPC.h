// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakamaBPExtension.h"
#include "NakamaProxy.h"
#include "NakamaRPC.generated.h"

USTRUCT(BlueprintType)
struct FNakamaRPCResponse {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Payload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Key;

	FNakamaRPCResponse(NAKAMA_NAMESPACE::NRpc RPC)
	{
		ID = FString(RPC.id.c_str());
		Payload = FString(RPC.payload.c_str());
		Key = FString(RPC.httpKey.c_str());
	}
	FNakamaRPCResponse() : ID(""), Payload(""), Key("") {}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnyRpcResponse, FNakamaRPCResponse, SuccessResponse, FNakamaErrorResponse, ErrorResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnRpcSuccessResponse, FNakamaRPCResponse, SuccessResponse);

/**
 * RPC function.
 * https://heroiclabs.com/docs/runtime-code-basics/#an-example-module
 */
UCLASS()
class NAKAMABPEXTENSION_API UNakamaRPC : public UOnlineBlueprintCallProxyBase, 
	public TNakamaProxy<FNakamaRPCResponse, FOnRpcSuccessResponse, FOnAnyRpcResponse>
{
	GENERATED_BODY()

public:
	// Generate a delegate for the OnGetResult event

	void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", AutoCreateRefTerm = "SuccessDelegate, ErrorDelegate"), Category = "Nakama BP Extension")
	static UNakamaRPC* RPC(const FString RpcID, const FString Payload, const FOnRpcSuccessResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate);

private:

	UPROPERTY()
	FString RpcID;

	UPROPERTY()
	FString Payload;

	UPROPERTY(BlueprintAssignable)
	FOnAnyRpcResponse OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAnyRpcResponse OnError;
};
