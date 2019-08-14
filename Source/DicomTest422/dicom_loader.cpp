// Fill out your copyright notice in the Description page of Project Settings.


#include "dicom_loader.h"
#include "Engine/Texture2D.h"
#include "Paths.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

// Sets default values
Adicom_loader::Adicom_loader() {
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void Adicom_loader::BeginPlay() {
  Super::BeginPlay();
}

// Called every frame
void Adicom_loader::Tick(float DeltaTime) {
  Super::Tick(DeltaTime);
}

bool Adicom_loader::LoadDicomSingleFileTest(
  /* output */ UTexture2D*& dicom_texture) {

  TArray<short> signed_pixels = ReadSampleData();

  int32 width = 512;
  int32 height = 512;
  dicom_texture = UTexture2D::CreateTransient(width, height, PF_R16_SINT); // In D3D11, PF_R16_SINT = DXGI_FORMAT_R16_SINT: A single-component, 16-bit unsigned-integer format that supports 16 bits for the red channel.
  dicom_texture->CompressionSettings = TextureCompressionSettings::TC_Grayscale;
  dicom_texture->Filter = TextureFilter::TF_Bilinear;
  dicom_texture->SRGB = false;

  void* locked_bulk_data = dicom_texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
  FMemory::Memcpy(locked_bulk_data, signed_pixels.GetData(), sizeof(short) * signed_pixels.Num());
  dicom_texture->PlatformData->Mips[0].BulkData.Unlock();

  dicom_texture->UpdateResource();
  return true;
}

TArray<short> Adicom_loader::ReadSampleData() {
  const FString file_full_path = FPaths::GameDir() + "sample_data.txt";
  UE_LOG(LogTemp, Warning, TEXT("%s"), *file_full_path);
  std::ifstream input_file(TCHAR_TO_UTF8(*file_full_path));

  std::string input_line;
  std::getline(input_file, input_line);

  // Split line by space(" ")
  std::stringstream line_for_split(input_line);
  std::string each_element;
  TArray<short> signed_16bit_pixels;
  signed_16bit_pixels.Reserve(512 * 512);
  while (std::getline(line_for_split, each_element, ' ')) {
    if (!each_element.empty()) {
      signed_16bit_pixels.Add((short)std::stoi(each_element));
    }
  }
  return signed_16bit_pixels;
}
