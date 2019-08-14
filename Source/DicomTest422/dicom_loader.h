// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "dicom_loader.generated.h"

UCLASS()
class DICOMTEST422_API Adicom_loader : public AActor {
  GENERATED_BODY()

public:
  // Sets default values for this actor's properties
  Adicom_loader();

protected:
  // Called when the game starts or when spawned
  virtual void BeginPlay() override;

public:
  // Called every frame
  virtual void Tick(float DeltaTime) override;

  UFUNCTION(BlueprintCallable, Category = "DicomLoader")
    bool LoadDicomSingleFileTest(
      /* output */ UTexture2D*& dicom_image);

private:
  TArray<short> ReadSampleData();
};
