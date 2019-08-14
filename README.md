# SimpleDicomTest422
I'd like to visualize DICOM CT data on Unreal Engine 4. In most cases, CT data is expressed as a sequence of 16bit signed integer.

And to visualize the data, we have to set Window Center, and Window Width.

So I'd like to use 16bit signed integer array for **UTexture2D** and map the color at runtime through the dynamic material.

Unreal Engine 4 seems to be able to handle the 16bit signed integer at least on the code level, by setting **PF_R16_SINT**.

Here is the code:
~~~
  UTexture2D* dicom_texture;
  
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
~~~

And here is the material I made to handle Window Center and Window Width.

![image](https://user-images.githubusercontent.com/8625552/63037146-71fc3900-bef9-11e9-96de-816591b272b4.png)

However the result is the following.

![image](https://user-images.githubusercontent.com/8625552/63037230-a1ab4100-bef9-11e9-9207-d61ff5fb4e78.png)

The image should be like this (opend in another software (ImageJ)).

![image](https://user-images.githubusercontent.com/8625552/63037305-cdc6c200-bef9-11e9-89f5-e4a90fa087a0.png)

I wonder if **PF_R16_SINT** is controllable via a material blueprints.

Do I have to write some very complicating shader and the associated C++ code (ENQUEUE_UNIQUE_RENDER_COMMAND_... or something like that) ?
