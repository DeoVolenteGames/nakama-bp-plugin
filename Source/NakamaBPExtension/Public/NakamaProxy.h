// Copyright 2021 DeoVolenteGames

#pragma once

#include "CoreMinimal.h"
#include <OnlineBlueprintCallProxyBase.h>
#include "NakamaError.h"
#include "NakamaBPExtension.h"
#include "NakamaProxy.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnErrorResponse, FNakamaErrorResponse, ErrorResponse);

/**
 * Super jank way of setting up common boilerplate for Nakama async nodes
 * https://ue4community.wiki/legacy/Creating_Asynchronous_Blueprint_Nodes
 */
template<typename SuccessResponse, typename OnSuccessResponse, typename OnAnyResponse>
class NAKAMABPEXTENSION_API TNakamaProxy
{
protected:
	void BroadcastError(OnAnyResponse ResponseErrorFunc, const NAKAMA_NAMESPACE::NError& ErrorMessage);
	void BroadcastError(OnAnyResponse ResponseErrorFunc, const NAKAMA_NAMESPACE::NRtError& ErrorMessage);
	void BroadcastError(OnAnyResponse ResponseErrorFunc, const FString ErrorMessage);
	void BroadcastSuccess(OnAnyResponse ResponseSuccessFunc, SuccessResponse Success);

	OnSuccessResponse OptionalSuccessFunc;
	FOnErrorResponse OptionalErrorFunc;
};

template<typename SuccessResponse, typename OnSuccessResponse, typename OnAnyResponse>
inline void TNakamaProxy<SuccessResponse, OnSuccessResponse, OnAnyResponse>::BroadcastError(OnAnyResponse ResponseErrorFunc, const NAKAMA_NAMESPACE::NError& ErrorMessage)
{
	UE_LOG(LogNakamaBPExtension, Error, TEXT("Nakama error: %s"), UTF8_TO_TCHAR(ErrorMessage.message.c_str()));
	OptionalErrorFunc.ExecuteIfBound(FNakamaErrorResponse(ErrorMessage));
	ResponseErrorFunc.Broadcast(SuccessResponse(), FNakamaErrorResponse(ErrorMessage));
};

template<typename SuccessResponse, typename OnSuccessResponse, typename OnAnyResponse>
inline void TNakamaProxy<SuccessResponse, OnSuccessResponse, OnAnyResponse>::BroadcastError(OnAnyResponse ResponseErrorFunc, const NAKAMA_NAMESPACE::NRtError& ErrorMessage)
{
	UE_LOG(LogNakamaBPExtension, Error, TEXT("Nakama error: %s"), UTF8_TO_TCHAR(ErrorMessage.message.c_str()));
	OptionalErrorFunc.ExecuteIfBound(FNakamaErrorResponse(ErrorMessage));
	ResponseErrorFunc.Broadcast(SuccessResponse(), FNakamaErrorResponse(ErrorMessage));
};

template<typename SuccessResponse, typename OnSuccessResponse, typename OnAnyResponse>
inline void TNakamaProxy<SuccessResponse, OnSuccessResponse, OnAnyResponse>::BroadcastError(OnAnyResponse ResponseErrorFunc, const FString ErrorMessage)
{
	UE_LOG(LogNakamaBPExtension, Error, TEXT("Nakama error: %s"), *ErrorMessage);
	OptionalErrorFunc.ExecuteIfBound(FNakamaErrorResponse(ErrorMessage));
	ResponseErrorFunc.Broadcast(SuccessResponse(), FNakamaErrorResponse(ErrorMessage));
};

template<typename SuccessResponse, typename OnSuccessResponse, typename OnAnyResponse>
inline void TNakamaProxy<SuccessResponse, OnSuccessResponse, OnAnyResponse>::BroadcastSuccess(OnAnyResponse ResponseSuccessFunc, SuccessResponse Success)
{
	OptionalSuccessFunc.ExecuteIfBound(Success);
	ResponseSuccessFunc.Broadcast(Success, FNakamaErrorResponse());
};
