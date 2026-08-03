// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class FPS_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	AWeapon();
	
	virtual void OnRep_Instigator() override;
	
	USkeletalMeshComponent* GetMesh1P() const;
	USkeletalMeshComponent* GetMesh3P() const;
	
	void AttachToOwningPawn() const;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="FPS|WeaponType")
	FGameplayTag WeaponType;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	//Weapon Mesh: 1st person view
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Mesh1P;
	
	//Weapon Mesh: 3rd person view
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> Mesh3P;

	void SetMeshVisibilities(APawn* OwningPawn) const;

};
