// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Combat/CombatComponent.h"
#include "GameFramework/Character.h"
#include "Interfaces/PlayerInterface.h"
#include "ShooterCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;


UCLASS()
class FPS_API AShooterCharacter : public ACharacter,public IPlayerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	/** PlayerInterface*/
	virtual FName GetWeaponAttachPoint_Implementation(const FGameplayTag& WeaponType) const override;
	virtual USkeletalMeshComponent* GetMesh1P_Implementation() const override;
	virtual USkeletalMeshComponent* GetMesh3P_Implementation() const override;
	/** ~PlayerInterface */
	
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	
	UFUNCTION(BlueprintCallable)
	FRotator GetFixedAimRotation() const;
	
	UPROPERTY(BlueprintReadOnly,Category="FPS|FABRIK")
	FTransform FABRIK_SocketTransform;
	
protected:
	// Called when the game starts or when spawned
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="FPS|Combat")
	TObjectPtr<UCombatComponent> Combat;
private:
	
	void Input_CycleWeapon();
	
	void Input_ReloadWeapon();
	
	void Input_FireWeapon_Pressed();
	void Input_FireWeapon_Released();
	
	void Input_Aim_Pressed();
	void Input_Aim_Released();
	
	void CalculateFABRIKSocketTransform();
	
	// 1st person view(arm)
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Mesh1P;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> FirstPersonCamera;
	
	UPROPERTY(EditAnywhere,Category="FPS|Input")
	TObjectPtr<UInputAction> CycleWeaponAction;
	
	UPROPERTY(EditAnywhere,Category="FPS|Input")
	TObjectPtr<UInputAction> FireWeaponAction;
	
	UPROPERTY(EditAnywhere,Category="FPS|Input")
	TObjectPtr<UInputAction> ReloadWeaponAction;
	
	UPROPERTY(EditAnywhere,Category="FPS|Input")
	TObjectPtr<UInputAction> AimWeaponAction;

};
