#pragma once
#using <mscorlib.dll>
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System;
using namespace System::IO;
using namespace System::Security::Cryptography;
using namespace System::Text;
using namespace std;

public ref class AesEncryption
{
private:
    static array<Byte>^ key = gcnew array<Byte>{ 0x54, 0x68, 0x69, 0x73, 0x20, 0x69, 0x73, 0x20, 0x61, 0x20, 0x6b, 0x65, 0x79, 0x20, 0x6f, 0x66 };
    array<Byte>^ iv;

public:
    AesEncryption()
    {
        this->iv = gcnew array<Byte>(16);
    }

    String^ Encrypt(String^ plainText)
    {
        IntPtr ptr = Marshal::StringToHGlobalAnsi(plainText);
        array<Byte>^ plainBytes = gcnew array<Byte>(plainText->Length);
        Marshal::Copy(ptr, plainBytes, 0, plainText->Length);
        Marshal::FreeHGlobal(ptr);

        AesManaged^ aes = gcnew AesManaged();
        try
        {
            aes->Key = key;
            aes->IV = iv;

            ICryptoTransform^ encryptor = aes->CreateEncryptor(aes->Key, aes->IV);

            MemoryStream^ ms = gcnew MemoryStream();
            try
            {
                CryptoStream^ cs = gcnew CryptoStream(ms, encryptor, CryptoStreamMode::Write);
                try
                {
                    cs->Write(plainBytes, 0, plainBytes->Length);
                    cs->FlushFinalBlock();
                }
                finally
                {
                    delete cs;
                }

                array<Byte>^ encryptedBytes = ms->ToArray();
                return Convert::ToBase64String(encryptedBytes);
            }
            finally
            {
                delete ms;
            }
        }
        finally
        {
            aes = nullptr;
        }
    }

    String^ Decrypt(String^ encryptedText)
    {
        array<Byte>^ encryptedBytes = Convert::FromBase64String(encryptedText);

        AesManaged^ aes = gcnew AesManaged();
        try
        {
            aes->Key = key;
            aes->IV = iv;

            ICryptoTransform^ decryptor = aes->CreateDecryptor(aes->Key, aes->IV);

            MemoryStream^ ms = gcnew MemoryStream(encryptedBytes);
            try
            {
                CryptoStream^ cs = gcnew CryptoStream(ms, decryptor, CryptoStreamMode::Read);
                try
                {
                    array<Byte>^ decryptedBytes = gcnew array<Byte>(encryptedBytes->Length);
                    int byteCount = cs->Read(decryptedBytes, 0, decryptedBytes->Length);

                    return Encoding::UTF8->GetString(decryptedBytes, 0, byteCount);
                }
                finally
                {
                    cs->Close();
                }
            }
            finally
            {
                ms->Close();
            }
        }
        finally
        {
            aes->Clear();
        }
    }
};