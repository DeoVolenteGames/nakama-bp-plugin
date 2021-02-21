// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <OnlineBlueprintCallProxyBase.h>
#include "NakamaError.h"
#include "NakamaProxy.h"
#include "NakamaBPExtension.h"
#include "NakamaSimpleProxy.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_DELEGATE(FOnSuccessResponse);
UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnyResponse, FNakamaErrorResponse, ErrorResponse);

/**
 * Super jank way of setting up common boilerplate for Nakama async nodes
 * https://wiki.unrealengine.com/Creating_Asynchronous_Blueprint_Nodes
 * Common setup for nodes that don't return anything when successful
 */
class NAKAMABPEXTENSION_API TNakamaSimpleProxy
{
protected:
	void BroadcastError(FOnAnyResponse ResponseErrorFunc, const NAKAMA_NAMESPACE::NError& ErrorMessage);
	void BroadcastError(FOnAnyResponse ResponseErrorFunc, const FString ErrorMessage);
	void BroadcastSuccess(FOnAnyResponse ResponseSuccessFunc);

	FOnSuccessResponse OptionalSuccessFunc;
	FOnErrorResponse OptionalErrorFunc;

	// I can't add these because I need them to be UPROPERTY()s
	// UPROPERTY(BlueprintAssignable)
	// FOnAnyResponse OnSuccess;
	// UPROPERTY(BlueprintAssignable)
	// FOnAnyResponse OnError;
};

inline void TNakamaSimpleProxy::BroadcastError(FOnAnyResponse ResponseErrorFunc, const NAKAMA_NAMESPACE::NError& ErrorMessage)
{
	UE_LOG(LogNakamaBPExtension, Error, TEXT("Nakama error: %s"), UTF8_TO_TCHAR(ErrorMessage.message.c_str()));
	OptionalErrorFunc.ExecuteIfBound(FNakamaErrorResponse(ErrorMessage));
	ResponseErrorFunc.Broadcast(FNakamaErrorResponse(ErrorMessage));
};

inline void TNakamaSimpleProxy::BroadcastError(FOnAnyResponse ResponseErrorFunc, const FString ErrorMessage)
{
	UE_LOG(LogNakamaBPExtension, Error, TEXT("Nakama error: %s"), *ErrorMessage);
	OptionalErrorFunc.ExecuteIfBound(FNakamaErrorResponse(ErrorMessage));
	ResponseErrorFunc.Broadcast(FNakamaErrorResponse(ErrorMessage));
};

inline void TNakamaSimpleProxy::BroadcastSuccess(FOnAnyResponse ResponseSuccessFunc)
{
	OptionalSuccessFunc.ExecuteIfBound();
	ResponseSuccessFunc.Broadcast(FNakamaErrorResponse());
};
