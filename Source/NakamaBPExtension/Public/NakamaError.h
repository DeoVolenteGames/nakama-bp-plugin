// Copyright 2021 DeoVolenteGames

#pragma once

#include "CoreMinimal.h"
#include "NakamaUnreal.h"
#include "NakamaError.generated.h"

USTRUCT(BlueprintType, Category = "Nakama BP Extension")
struct NAKAMABPEXTENSION_API FNakamaErrorResponse {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Message;

	FNakamaErrorResponse(const NAKAMA_NAMESPACE::NError& Error)
	{
		Message = Error.message.c_str();
	}
	FNakamaErrorResponse(const NAKAMA_NAMESPACE::NRtError& Error)
	{
		Message = Error.message.c_str();
	}
	FNakamaErrorResponse(const FString Message) : Message(Message) {}
	FNakamaErrorResponse() {}
};
