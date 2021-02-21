// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NakamaBPExtension.h"
#include "NakamaProxy.h"
#include "NakamaAuthenticate.generated.h"

// TODO: Better naming scheme
// TODO: Make this a generic session struct?
USTRUCT(BlueprintType)
struct FNakamaAuthenticateSessionResponse {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Token;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Username;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString UserID;

	FNakamaAuthenticateSessionResponse(NAKAMA_NAMESPACE::NSessionPtr NewSession)
	{
		Token = FString(NewSession->getAuthToken().c_str());
		Username = FString(NewSession->getUsername().c_str());
		UserID = FString(NewSession->getUserId().c_str());
	}
	FNakamaAuthenticateSessionResponse() : Token(""), Username(""), UserID("") {}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnyAuthResponse, FNakamaAuthenticateSessionResponse, SuccessResponse, FNakamaErrorResponse, ErrorResponse);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnAuthSuccessResponse, FNakamaAuthenticateSessionResponse, SuccessResponse);

/**
 * Several different authentication methods.
 * https://heroiclabs.com/docs/authentication/
 */
UCLASS()
class NAKAMABPEXTENSION_API UNakamaAuthenticate : public UOnlineBlueprintCallProxyBase, 
	public TNakamaProxy<FNakamaAuthenticateSessionResponse, FOnAuthSuccessResponse, FOnAnyAuthResponse>
{
	GENERATED_BODY()

public:
	void Activate() override;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", AutoCreateRefTerm = "SuccessDelegate, ErrorDelegate"), Category = "Nakama BP Extension|Authentication")
	static UNakamaAuthenticate* AuthenticateDevice(const FString DeviceID, const FString Username, const bool Create, const FOnAuthSuccessResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", AutoCreateRefTerm = "SuccessDelegate, ErrorDelegate"), Category = "Nakama BP Extension|Authentication")
    static UNakamaAuthenticate* AuthenticateCustom(const FString CustomID, const FString Username, const bool Create, const FOnAuthSuccessResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate);
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", AutoCreateRefTerm = "SuccessDelegate, ErrorDelegate"), Category = "Nakama BP Extension|Authentication")
    static UNakamaAuthenticate* AuthenticateEmail(const FString EmailAddress, const FString Password, const FString Username, const bool Create, const FOnAuthSuccessResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate);
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", AutoCreateRefTerm = "SuccessDelegate, ErrorDelegate"), Category = "Nakama BP Extension|Authentication")
	static UNakamaAuthenticate* AuthenticateFacebook(const FString AccessToken, const FString Username, const bool Create, const bool ImportFriends, const FOnAuthSuccessResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate);
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", AutoCreateRefTerm = "SuccessDelegate, ErrorDelegate"), Category = "Nakama BP Extension|Authentication")
	static UNakamaAuthenticate* AuthenticateGoogle(const FString AccessToken, const FString Username, const bool Create, const FOnAuthSuccessResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate);
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", AutoCreateRefTerm = "SuccessDelegate, ErrorDelegate"), Category = "Nakama BP Extension|Authentication")
    static UNakamaAuthenticate* AuthenticateSteam(const FString AccessToken, const FString Username, const bool Create, const FOnAuthSuccessResponse& SuccessDelegate, const FOnErrorResponse& ErrorDelegate);

private:
	enum EAuthType {
		Undefined, Device, Email, Facebook, Google, Steam, Custom
	};
	EAuthType AuthType;

	UPROPERTY()
	FString TokenOrID;

	UPROPERTY()
	FString Username;

	// Additional password for email authentication
	UPROPERTY()
	FString Password;

	UPROPERTY()
	bool Create;

	// Additional Import Friends bool for Facebook authentication
	UPROPERTY()
	bool ImportFriends;

	UPROPERTY(BlueprintAssignable)
	FOnAnyAuthResponse OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAnyAuthResponse OnError;
};
