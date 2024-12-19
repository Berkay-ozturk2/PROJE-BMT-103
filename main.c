#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // Küçük harfe dönüştürme için gerekli kütüphane

#define KOTA_GB 6.0
#define MB_TO_GB 1024.0
#define KOTA_ASIM_UCRETI 0.011719

// Prototip fonksiyonlar
void tr_to_ing(char tr[15]);
void tolowercase(char kucuk[10]);

// Ana fonksiyon
int main() {
    FILE *adsl, *fatura; // Dosya işaretçileri
    char ay_adi[10], satir[40], adsl_ay[10];
    int gun;
    float yukleme, indirme;
    float toplam_yukleme = 0.0, toplam_indirme = 0.0, asim_ucreti = 0.0;

    // Kullanıcıdan ay adını al ve ay_adi dizisine tanımla
    printf("Hangi ayin faturasini istiyorsunuz:");
    scanf("%s", ay_adi);

    // Girilen ay adını küçülten fonksiyon
    tolowercase(ay_adi);
    // Türkçe karakterleri İngilizce karakterlere çeviren fonksiyon
    tr_to_ing(ay_adi);

    // adsl.txt dosyasını aç ve oku
    adsl = fopen("C:\\Users\\USER\\Desktop\\adsl.txt", "r");
    if (adsl == NULL) { // Dosya bulunamazsa aşağıdaki mesaj yazılır
        printf("adsl.txt dosyasi acilamadi!\n");
        return 1;
    }

    // Dosyayı satır satır oku
    while (fgets(satir, sizeof(satir), adsl)) {
        // sscanf diziden veriyi okur ve veriyi değişkenlere atar
        sscanf(satir, "%s %d %f %f", adsl_ay, &gun, &yukleme, &indirme);

        // adsl.txt dosyasındaki ay adının harflerini küçük harflere çevirir
        tolowercase(adsl_ay);

        // Kullanıcının girdiği ay ile adsl.txt dosyasındaki ayı karşılaştırır
        if (strcmp(ay_adi, adsl_ay) == 0) {
            toplam_yukleme += yukleme;
            toplam_indirme += indirme;
        }
    }

    fclose(adsl); // adsl.txt dosyasını kapat

    // MegaBayt'tan GigaBayt'a çevir
    toplam_yukleme /= MB_TO_GB;
    toplam_indirme /= MB_TO_GB;

    // Kota aşım durumunu kontrol et ve hesapla
    if (toplam_indirme > KOTA_GB) {
        float asim = (toplam_indirme - KOTA_GB) * MB_TO_GB;
        asim_ucreti = asim * KOTA_ASIM_UCRETI;
    }

    // fatura.txt dosyasını oluştur ve yaz
    fatura = fopen("C:\\Users\\USER\\Desktop\\fatura.txt", "w");
    if (fatura == NULL) { // Dosya oluşturulamazsa aşağıdaki mesaj yazılır
        printf("fatura.txt dosyasi olusturulamadi!\n");
        return 1;
    }
    // fatura.txt dosyasının içine yazdırma
    fprintf(fatura, "%s 2012\n", ay_adi);
    fprintf(fatura, "Toplam Yükleme: %.2f GB\n", toplam_yukleme);
    fprintf(fatura, "Toplam İndirme: %.2f GB\n", toplam_indirme);
    fprintf(fatura, "Kota Aşım Ücreti: %.2f TL\n", asim_ucreti);

    fclose(fatura); // fatura.txt dosyasını kapat

    printf("Faturaniz basariyla olusturuldu.\n");
    return 0;
}

// Harf küçültme fonksiyonu
void tolowercase(char kucuk[10]) {
    for (int i = 0; kucuk[i] != 0; i++) {
         kucuk[i] = tolower(kucuk[i]);
    }
}

// Türkçe karakterleri İngilizce karakterlere çevirme fonksiyonu
void tr_to_ing(char tr[15]) {
    for (int i = 0; tr[i] != 0; i++) {
        unsigned char c = tr[i];

        // Türkçe karakterlerin ASCII kodlarını karşılaştırıp yeni karakter atama
        switch (c) {
            case 158: // 'Ş' ASCII değeri 158
            case 159: // 'ş' ASCII değeri 159
                tr[i] = 's';
            break;

            case 152: // 'İ' ASCII değeri 152
            case 141: // 'ı' ASCII değeri 141
                tr[i] = 'i';
            break;

            case 154: // 'Ü' ASCII değeri 154
            case 129: // 'ü' ASCII değeri 129
                tr[i] = 'u';
            break;

            case 166: // 'Ğ' ASCII değeri 166
            case 167: // 'ğ' ASCII değeri 167
                tr[i] = 'g';
            break;

            default:
                // Hiçbir eşleşme yoksa karakteri değiştirme
                    break;
        }
    }
}