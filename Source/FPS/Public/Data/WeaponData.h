// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamePlayTagContainer.h"
#include "Engine/DataAsset.h"
#include "WeaponData.generated.h"

class UBlendSpace;
class UAnimSequence;

USTRUCT(BlueprintType)
struct FPlayerAnims
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UAnimSequence> IdelAnim= nullptr;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UAnimSequence> AimIdleAnim= nullptr;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UAnimSequence> CrouchIdelAnim= nullptr;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UAnimSequence> SprintAnim= nullptr;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UBlendSpace> AimOffset_Hip;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UBlendSpace> AimOffset_Aim;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UBlendSpace> Strafe_Standing;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UBlendSpace> Strafe_Crouching;
};

UCLASS()
class FPS_API UWeaponData : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly,Category="FPS|WeaponData|Weapons")
	TMap<FGameplayTag,FName> GripPoints;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="FPS|WeaponData|FirstPerson")
	TMap<FGameplayTag,FPlayerAnims> FisrtPersonAnims;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="FPS|WeaponData|ThirdPerson")
	TMap<FGameplayTag,FPlayerAnims> ThirdPersonAnims;
	
};
