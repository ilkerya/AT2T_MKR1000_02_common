

20:49:19.819 -> ECCX08 Serial Number = 012363B32B0B7E53AF
20:49:19.819 ->
20:49:19.853 -> The ECCX08 on your board is not locked, would you like to PERMANENTLY configure and lock it now? (y/N) [N]: yyy
20:49:55.899 -> ECCX08 locked successfully
20:49:55.899 ->
20:49:55.899 -> Hi there, in order to generate a new CSR for your board, we'll need the following information ...
20:49:55.899 ->
20:49:55.899 -> Country Name (2 letter code) []:
20:50:01.202 -> State or Province Name (full name) []:
20:50:15.346 -> Locality Name (eg, city) []:
20:50:17.142 -> Organization Name (eg, company) []:
20:50:18.603 -> Organizational Unit Name (eg, section) []:
20:50:21.798 -> Common Name (e.g. server FQDN or YOUR name) [012363B32B0B7E53AF]: My_IoT_Device
20:50:45.806 -> What slot would you like to use? (0 - 4) [0]: 0
20:50:59.957 -> Would you like to generate a new private key? (Y/n) [Y]: Y
20:51:11.812 ->
20:51:12.116 -> Here's your CSR, enjoy!
20:51:12.116 ->
20:51:12.116 -> -----BEGIN CERTIFICATE REQUEST-----
20:51:12.116 -> MIHSMHoCAQAwGDEWMBQGA1UEAxMNTXlfSW9UX0RldmljZTBZMBMGByqGSM49AgEGCCqGSM49AwEH
20:51:12.116 -> A0IABCJYT+PRF7WwuMewA13SdOW7kO7DOXXVhx2UQ33+VaIjydoPc+vYfRJ5cDNFLxIp11fEq/RF
20:51:12.116 -> MGcq62R1L+rLEVWgADAKBggqhkjOPQQDAgNIADBFAiAB0/T7FcdsEfncZXR9RVC/hLzQSycZ4O2I
20:51:12.116 -> fRQgd8Xb8AIhAJ0bx+mVs04LyI7qFhd/CzJ6slwbi0Upql4htuRHSTYO
20:51:12.116 -> -----END CERTIFICATE REQUEST-----
20:51:12.116 ->



https://create.arduino.cc/projecthub/Arduino_Genuino/securely-connecting-an-arduino-mkr-wifi-1010-to-aws-iot-core-a9f365?f=1'



// created by arduino


-----BEGIN CERTIFICATE REQUEST-----
20:51:12.116 -> MIHSMHoCAQAwGDEWMBQGA1UEAxMNTXlfSW9UX0RldmljZTBZMBMGByqGSM49AgEGCCqGSM49AwEH
20:51:12.116 -> A0IABCJYT+PRF7WwuMewA13SdOW7kO7DOXXVhx2UQ33+VaIjydoPc+vYfRJ5cDNFLxIp11fEq/RF
20:51:12.116 -> MGcq62R1L+rLEVWgADAKBggqhkjOPQQDAgNIADBFAiAB0/T7FcdsEfncZXR9RVC/hLzQSycZ4O2I
20:51:12.116 -> fRQgd8Xb8AIhAJ0bx+mVs04LyI7qFhd/CzJ6slwbi0Upql4htuRHSTYO
20:51:12.116 -> -----END CERTIFICATE REQUEST-----



Custom endpoint
ENABLED
This is your custom endpoint that allows you to connect to AWS IoT. Each of your Things has a REST API available at this endpoint.
This is also an important property to insert when using an MQTT client or the AWS IoT Device SDK.

Your endpoint is provisioned and ready to use. You can now start to publish and subscribe to topics.

Endpoint
a152coqmo1y6lb-ats.iot.us-west-2.amazonaws.com


// downloaded from AWS

-----BEGIN CERTIFICATE-----
MIICiDCCAXCgAwIBAgIUZwcBXCAw0TPoCoAepPAr0mlgHXswDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTE5MDcyNjE5MTIw
MVoXDTQ5MTIzMTIzNTk1OVowGDEWMBQGA1UEAxMNTXlfSW9UX0RldmljZTBZMBMG
ByqGSM49AgEGCCqGSM49AwEHA0IABCJYT+PRF7WwuMewA13SdOW7kO7DOXXVhx2U
Q33+VaIjydoPc+vYfRJ5cDNFLxIp11fEq/RFMGcq62R1L+rLEVWjYDBeMB8GA1Ud
IwQYMBaAFP9eq5CVf85zgj674twLh7g1WA0EMB0GA1UdDgQWBBTTgx1xuaB4LDvz
OnaG4dIT1frQ+DAMBgNVHRMBAf8EAjAAMA4GA1UdDwEB/wQEAwIHgDANBgkqhkiG
9w0BAQsFAAOCAQEA2INBf3troAaD8mflvWi9AADJQRaARFhHbBW9LObT7jHa59Sl
1RswbQnY5wNay3f0s2rJCDsFrE4IlyVVfxzoduXYn3orwtiyJ8QH65yh6PJBihU7
pPp57F7CulB9aHCuw8EvotUtqLDF3J1XYXJYSXrUGBkWeQI7BBaDmJFVNmY/6ZV0
HYu4PPGOT+xIa5poAjLLw2/JFPL3zx6UZtHEUt2v6PBZ1nWvzKAW9fu4JlBES4WN
DgGR95t2G8z92/acJE3pwfFRz58nS/ThSwtgesAj9HaVBxglGl2vG1esglfwrOZC
IWXZX5ZS9N4SbYOk4enS+EuyE1aRARqIoGNlUQ==
-----END CERTIFICATE-----

