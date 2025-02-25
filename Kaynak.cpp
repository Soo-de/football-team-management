//***********************************************************************************************************************
//**                                                                                                                   **
//**                                     SAKARYA ÜNÝVERSÝTESÝ                                                          **
//**                          BÝLGÝSAYAR VE BÝLÝÞÝM BÝLÝMLERÝ FAKÜLTESÝ                                                **
//**                                BÝLGÝSAYAR MÜHENDÝSLÝÐÝ BÖLÜMÜ                                                     **
//**                                                                                                                   **
//**                                  PROJE NUMARASI..: 1                                                              **
//**                                  ÖÐRENCÝ ADI.....: SUDE ANDURMAN                                                  **
//**                                  ÖÐRENCÝ NUMARASI: b231210005                                                     **
//**                                  DERS GRUBU......: A                                                              **
//**                                                                                                                   ** 
//**                                                                                                                   **  
//**                Amaç:Futbol ligi takip sistemi gerçekleþtiren bir program hazýrlamak                               **
//**                                                                                                                   **
//**                                                                                                                   **  
//**                                                                                                                   **
//***********************************************************************************************************************

#include <iostream>
#include <fstream>
#include <iomanip>
#include <locale.h>
#include <vector>
#include <ctime>
using namespace std;

class futbolcu
{
public:
	int tc;
	int lisansno;
	int ucreti;
	string dogumt;
	string ad;
	string soyad;
	string mevki;

	futbolcu() :tc(0), lisansno(0), ucreti(0), dogumt(" "), ad(" "), soyad(" "), mevki(" ")
	{}

	void FutbolcuAl()
	{
		system("CLS");
		char dongukontrol = 'e';
		int tckontrol;
		cout << "Futbolcunun tcsi (4 haneli) : "; cin >> tckontrol; cout << endl;
		if (tckontrol < 1000 || tckontrol > 9999)//ALINAN TCNÝN SINIRLANDIRILMASI
		{
			do
			{
				if (tckontrol < 1000 || tckontrol > 9999)
				{
					cout << "Geçersiz TC kimlik numarasý girdiniz lütfen 4 haneli olmasýna dikkat ediniz." << endl;
					cout << "Futbolcunun tcsi (4 haneli) : "; cin >> tckontrol; cout << endl;
				}
				else
					dongukontrol = 'h';
			} while (dongukontrol != 'h');
		}
		dongukontrol = 'e';
		int sayac = 0;
		do//ALINAN TC NÝN DÝÐER TCLER ÝLE AYNI OLMAMASI KONTROLÜ ÝÇÝN 
		{
			do
			{
				sayac = 0;
				ifstream DosyaOku("futbolcu.txt");
				while (DosyaOku >> tc >> lisansno >> ad >> soyad >> dogumt >> mevki >> ucreti)
				{
					if (tckontrol == tc)
					{
						cout << "Bu TC numaralý baþka bir oyuncu bulunmaktadýr lütfen tekrar giriniz." << endl;
						cout << "Futbolcunun tcsi (4 haneli) : "; cin >> tckontrol; cout << endl;
						if (tckontrol < 1000 || tckontrol > 9999)
						{
							do
							{
								if (tckontrol < 1000 || tckontrol > 9999)
								{
									cout << "Geçersiz TC kimlik numarasý girdiniz lütfen 4 haneli olmasýna dikkat ediniz." << endl;
									cout << "Futbolcunun tcsi (4 haneli) : "; cin >> tckontrol; cout << endl;
								}
								else
									dongukontrol = 'c';
								
							} while (dongukontrol != 'c');
						}
						else
							dongukontrol = 'c';
						sayac=1;
					}
				}
				dongukontrol = 'c';
				DosyaOku.close();
			} while (dongukontrol != 'c');
			if (sayac == 0)//BÜTÜN TCLERLE TEKRAR KARÞILAÞTIRILIP AYNI OLMADIÐINDA DÖNGÜDEN ÇIKIÞ ÝÇÝN 
				dongukontrol = 'h';
		} while (dongukontrol != 'h');
		tc = tckontrol;
		cout << "Futbolcunun lisans numarasý : "; cin >> lisansno; cout << endl;
		cout << "Futbolcunun adý : "; cin>>ad; cout << endl;
		cout << "Futbolcunun soyadý : "; cin >> soyad; cout << endl;
		cout << "Futbolcunun doðum tarihi (ÖRN; 2.12.2000) : "; cin >> dogumt; cout << endl;
		cout << "Futbolcunun mevkisi (boþluk býrakmadan yazýnýz) : "; cin >> mevki; cout << endl;
		cout << "Futbolcunun ücreti : "; cin >> ucreti; cout << endl;
	}
	void FutbolcuKaydet();
	void FutbolcuSil();
	void FutbolcuGuncelle();
	void FutbolculariListele();
};	
void futbolcu::FutbolcuKaydet()//FUTBOLCU KAYDININ TAMAMLANMASI
{
	ofstream DosyayaYaz("futbolcu.txt", ios::app);
	FutbolcuAl();
	DosyayaYaz << tc << ' ' << lisansno << ' ' << ad << ' ' << soyad << ' ' << dogumt << ' ' << mevki << ' ' << ucreti << endl;
	DosyayaYaz.close();
}

void futbolcu::FutbolcuSil()
{
	string takimadi;
	system("CLS");
	int kontrol=0;
	int sayac = 0;
	ifstream DosyaOku("futbolcu.txt");
	ofstream DosyaYenile("futbolcu.tmp");
	int silinecekoyuncu;
	char dongukontrol='e';
	do
	{
		kontrol=0;
		cout << "Silmek istediðiniz futbolcunun tc sini giriniz : "; cin >> silinecekoyuncu; cout << endl;
		ifstream DosyaOkuTO("takimoyuncu.txt");
		while (DosyaOkuTO >> takimadi >> tc >> ad >> soyad)//SÝLÝNMEK ÝSTENEN OYUNCU HERHANGÝ BÝR TAKIMDAYSA ÝÞLEMÝN ENGELLENMESÝ
		{
			if (silinecekoyuncu == tc)
			{
				cout << "Bu oyuncu þuanda aktif bir takýmda bulunuyor." << endl;
				cout << "Lütfen önce silmek istediðiniz oyuncuyu takýmdan çýkarýnýz. " << endl << endl;
				kontrol = 1;
				cout << "_______________________________________________" << endl;
				cout << "|" << setw(47) << "|" << endl;
				cout << "|" << setw(42) << "*BAÞARISIZ ÝÞLEM MENÜYE DÖNEBÝLÝRSÝNÝZ*" << setw(5) << "|" << endl;
				cout << "|" << setw(47) << "|" << endl;
				cout << "-----------------------------------------------" << endl << endl;
			}
		}
		if (kontrol == 1)
			break;
		while (DosyaOku >> tc >> lisansno >> ad >> soyad >> dogumt >> mevki >> ucreti)//OYUNCU SÝLME ÝÞLEMÝNÝN YAPILMASI
		{
			if (silinecekoyuncu == tc)
			{
				sayac++;
				cout << setw(20) << "*Silinecek oyuncunun bilgileri*" << endl;
				cout << "---------------------------------------" << endl;
				cout << "Oyuncu : " << ad << " " << soyad << endl;
				cout << "Doðum tarihi : " << dogumt << endl;
				cout << "Lisans No :" << lisansno << endl;
				cout << "Mevki : " << mevki << endl;
				cout << "Aldýðý ücret : " << ucreti << endl;
				dongukontrol = 'e';
			}
			else
			{
				DosyaYenile << tc << ' ' << lisansno << ' ' << ad << ' ' << soyad << ' ' << dogumt << ' ' << mevki << ' ' << ucreti << endl;
			}
		}
		if (sayac == 0)//BULUNMAYAN BÝR TC GÝRÝLDÝÐÝNDE ÝÞLEMÝN TEKRARLANMASI
		{
			cout << "______________________________________________" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "|" << setw(35) << "*GEÇERSÝZ TC NO GÝRDÝNÝZ*" << setw(11) << "|" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "|" << setw(39) << "*LÜTFEN GEÇERLÝ BÝR TC NO GÝRÝNÝZ*" << setw(7) << "|" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "----------------------------------------------" << endl << endl;
			cout << "_______________________________________________" << endl;
			cout << "|" << setw(47) << "|" << endl;
			cout << "|" << setw(42) << "*BAÞARISIZ ÝÞLEM MENÜYE DÖNEBÝLÝRSÝNÝZ*" << setw(5) << "|" << endl;
			cout << "|" << setw(47) << "|" << endl;
			cout << "-----------------------------------------------" << endl << endl;
			dongukontrol='c';
			
		}
		else if (sayac != 0)
		{
			cout << "_______________________________________________" << endl;
			cout << "|" << setw(47) << "|" << endl;
			cout << "|" << setw(42) << "*BAÞARILI ÝÞLEM MENÜYE DÖNEBÝLÝRSÝNÝZ*" << setw(5) << "|" << endl;
			cout << "|" << setw(47) << "|" << endl;
			cout << "-----------------------------------------------" << endl << endl;
		}
		DosyaYenile.close();
		DosyaOku.close();
		remove("futbolcu.txt");
		rename("futbolcu.tmp", "futbolcu.txt");//DÖNGÜ ÝÇÝNE YAZMA NEDENÝ VAR...
		if (dongukontrol == 'c')
			break;
	} while (dongukontrol != 'e');
	
}
void futbolcu::FutbolcuGuncelle()
{
	system("CLS");
	ifstream DosyaOku("futbolcu.txt");
	ofstream DosyaGuncel("futbolcu.tmp");
	int guncellenecekoyuncu;
	int tckontrol;
	char dongukontrol;
	cout << "Güncellemek istediðiniz oyuncunun TC sini giriniz."; cin >> guncellenecekoyuncu; cout << endl;
	while (DosyaOku >> tc >> lisansno >> ad >> soyad >> dogumt >> mevki >> ucreti)
	{
		if (guncellenecekoyuncu == tc)
		{
			cout << setw(20) << "*Güncellenecek oyuncunun bilgileri*" << endl;
			cout << "---------------------------------------" << endl;
			cout << "Oyuncu : " << ad << " " << soyad << endl;
			cout << "Doðum tarihi : " << dogumt << endl;
			cout << "Lisans No :" << lisansno << endl;
			cout << "TC : " << tc << endl;
			cout << "Mevki : " << mevki << endl;
			cout << "Aldýðý ücret : " << ucreti << endl;
			cout << "---------------------------------------" << endl << endl;
			cout << setw(20) << "*Güncel bilgileri giriniz*" << endl;
			cout << "TC (4 haneli) : "; cin >> tckontrol;
			if (tckontrol < 1000 || tckontrol > 9999)//TC SINIRLAMASIKONTROLÜ
			{
				do
				{
					if (tckontrol < 1000 || tckontrol > 9999)
					{
						cout << "Geçersiz TC kimlik numarasý girdiniz lütfen 4 haneli olmasýna dikkat ediniz." << endl;
						cout << "Futbolcunun tcsi (4 haneli) : "; cin >> tckontrol; cout << endl;
					}
					else
						dongukontrol = 'h';
				} while (dongukontrol != 'h');
			}
			dongukontrol = 'e';
			int sayac = 0;
			do//ALINAN YENÝ TCNÝN TEKRARDAN DÝÐERLERÝYLE AYNI OLUP OLMAMA KONTROLÜNÜN YAPILMASI
			{
				do
				{
					sayac = 0;
					ifstream DosyaOku("futbolcu.txt");
					while (DosyaOku >> tc >> lisansno >> ad >> soyad >> dogumt >> mevki >> ucreti)
					{
						if (tckontrol == tc)
						{
							cout << "Bu TC numaralý baþka bir oyuncu bulunmaktadýr lütfen tekrar giriniz." << endl;
							cout << "Futbolcunun tcsi (4 haneli) : "; cin >> tckontrol; cout << endl;
							if (tckontrol < 1000 || tckontrol > 9999)
							{
								do
								{
									if (tckontrol < 1000 || tckontrol > 9999)
									{
										cout << "Geçersiz TC kimlik numarasý girdiniz lütfen 4 haneli olmasýna dikkat ediniz." << endl;
										cout << "Futbolcunun tcsi (4 haneli) : "; cin >> tckontrol; cout << endl;
									}
									else
										dongukontrol = 'c';

								} while (dongukontrol != 'c');
							}
							else
								dongukontrol = 'c';
							sayac = 1;
						}
					}
					dongukontrol = 'c';
					DosyaOku.close();
				} while (dongukontrol != 'c');
				if (sayac == 0)//BÜTÜN TCLERLE KARÞILAÞTIRMA BÝTTÝKTEN SONRA AYNI OLMADIYSA DÖNGÜDEN ÇIKIÞ ÝÇÝN 
					dongukontrol = 'h';
			} while (dongukontrol != 'h');
			tc = tckontrol;
			cout << "Lisans No : "; cin >> lisansno;
			cout << "Ad : "; cin >> ad;
			cout << "Soyad : "; cin >> soyad;
			cout << "Doðum tarihi (1/2/2000) : "; cin >> dogumt;
			cout << "Mevki : "; cin >> mevki;
			cout << "Ücret : "; cin >> ucreti;
			DosyaGuncel << tc << ' ' << lisansno << ' ' << ad << ' ' << soyad << ' ' << dogumt << ' ' << mevki << ' ' << ucreti << endl;
		}
		else
			DosyaGuncel << tc << ' ' << lisansno << ' ' << ad << ' ' << soyad << ' ' << dogumt << ' ' << mevki << ' ' << ucreti << endl;
	}
	DosyaGuncel.close();
	DosyaOku.close();
	remove("futbolcu.txt");
	rename("futbolcu.tmp", "futbolcu.txt");
}
void futbolcu::FutbolculariListele()
{
	system("CLS");
	ifstream DosyaOku("futbolcu.txt");
	while (DosyaOku >> tc >> lisansno >> ad >> soyad >> dogumt >> mevki >> ucreti)
	{
		cout << "_________________________________________" << endl;
		cout << "Futbolcu : " << ad << " " << soyad << endl;
		cout << "Doðum tarihi : " << dogumt << endl;
		cout << "TC : " << tc << endl;
		cout << "Lisans NO : " << lisansno << endl;
		cout << "Mevki : " << mevki << endl;
		cout << "Ücreti : " << ucreti << endl;
		cout << "-----------------------------------------" << endl;
	}
}
class takim : public futbolcu
{
public:
	int takimno;
	long long int telefon;
	int oyuncusayisi;
	string yoneticiadi;
	string yoneticisoyadi;
	string takimadi;
	string adres;

	takim():futbolcu(),takimno(0),telefon(0),oyuncusayisi(0),yoneticiadi(" "),yoneticisoyadi(" "),takimadi(" "),adres(" ")
	{}
	
	void TakimAl()//TAKIM EKLEMEK ÝÇÝN
	{
		static int takimnobelirleme=1;
		system("CLS");
		string takimadkontrol;
		char dongukontrol = 'e';
		int kontrol=0;
		ifstream DosyaOku("takim.txt");
		while (DosyaOku >> takimno >> takimadi >> yoneticiadi >> yoneticisoyadi >> telefon >> adres >> oyuncusayisi)
		{
			if (takimnobelirleme == takimno)//TAKIM EKLENDÝÐÝNDE TAKIM NUMARASININ SIRAYA GÖRE BELÝRLENMESÝ 
				takimnobelirleme++;
		}
		DosyaOku.close();
		do
		{
			cout << "Takým adý : "; cin >> takimadkontrol;
			do
			{
				kontrol = 0;
				ifstream DosyaOku("takim.txt");
				while (DosyaOku >> takimno >> takimadi >> yoneticiadi >> yoneticisoyadi >> telefon >> adres >> oyuncusayisi)
				{
					if (takimadkontrol == takimadi)//AYNI TAKIM ADININ KULLANILMASININ ENGELLENMESÝ
					{
						cout << endl<<"Kullanýlan bir takým adýný tekrardan kullanamazsýnýz " << endl;
						cout << "Lütfen baþka bir ismi giriniz" << endl<<endl;
						kontrol = 1;
					}
				}
				DosyaOku.close();
				dongukontrol = 'h';
			} while (dongukontrol != 'h');
			if (kontrol == 0)
				dongukontrol = 'c';
		} while (dongukontrol != 'c');
		takimadi = takimadkontrol;
		takimno = takimnobelirleme;
		takimnobelirleme++;
		cout << "Yönetici adý : "; cin >> yoneticiadi;
		cout << "Yönetici soyadý : "; cin >> yoneticisoyadi;
		cout << "Telefon numarasý : "; cin >> telefon;
		cout << "Adres : "; cin >> adres;
	}
	void TakimOlustur();
	void TakimSil();
	void EkleFutbolcu();
	void SilFutbolcu();
	void TakimListele();
};
void takim::TakimOlustur()//TAKIM EKLEM ÝÞLEMÝNÝN TAMAMLANMASI
{
	TakimAl();
	ofstream DosyayaYaz("takim.txt",ios::app);
	DosyayaYaz << takimno << ' ' << takimadi << ' ' << yoneticiadi << ' ' << yoneticisoyadi << ' ' << telefon << ' ' << adres << ' ' << oyuncusayisi << endl;
	DosyayaYaz.close();
}
void takim::TakimSil()
{
	system("CLS");
	int kontrol = 0;
	ofstream DosyaYenile("takim.tmp");
	string silinecektakim;
	do
	{
		cout << "Silmek istediðiniz takýmý giriniz : "; cin >> silinecektakim; cout << endl;
		ifstream DosyaOku("takim.txt");
		while (DosyaOku >> takimno >> takimadi >> yoneticiadi >> yoneticisoyadi >> telefon >> adres >> oyuncusayisi)
		{
			if (silinecektakim == takimadi)
			{
				kontrol=1;
				cout <<setw(20) <<"*Silinecek takýmýn bilgileri*" << endl;
				cout << "Takým numarasý : " << takimno<<endl;
				cout << "Takým adý : " << takimadi<<endl;
				cout << "Takým yöneticisi : " << yoneticiadi << " " << yoneticisoyadi << endl;
				cout << "Telefon : " << telefon << endl;
				cout << "Adres : " << adres << endl;
				cout << "Oyuncu sayisi : " << oyuncusayisi << endl;
				ifstream DosyaOkuTO("takimoyuncu.txt");
				ofstream DosyaYenile("takimoyuncu.tmp",ios::app);
				string takimadiTO;
				while (DosyaOkuTO >> takimadiTO >> tc >> ad >> soyad)//TAKIM SÝLÝNÝNCE ÝÇÝNDE BULUNAN OYUNCULARINDA TAKIMDAKÝ OYUNCULAR DOSYASINDAN SÝLÝNMESÝ
				{
					if (takimadi != takimadiTO)
					{
						DosyaYenile << takimadiTO << ' ' << tc << ' ' << ad << ' ' << soyad << endl;
					}
				}
				DosyaOkuTO.close();
				DosyaYenile.close();
				remove("takimoyuncu.txt");
				rename("takimoyuncu.tmp", "takimoyuncu.txt");
			}
			else//TAKIM SÝLÝNDÝKTEN SONRA DOSYANIN YENÝLENMESÝ
			{
				DosyaYenile << takimno << ' ' << takimadi << ' ' << yoneticiadi << ' ' << yoneticisoyadi << ' ' << telefon << ' ' << adres << ' ' << oyuncusayisi << endl;
			}
		}
		DosyaOku.close();
		if (kontrol == 0)//GÝRÝLEN TAKIMIN BULUNMAMASI DURUMU ÝÇÝN
		{
			cout << "______________________________________________" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "|" << setw(35) << "*GEÇERSÝZ TAKIM GÝRDÝNÝZ*" << setw(11) << "|" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "|" << setw(39) << "*LÜTFEN GEÇERLÝ BÝR TAKIM GÝRÝNÝZ*" << setw(7) << "|" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "----------------------------------------------" << endl << endl;
			system("PAUSE");
			system("CLS");
		}

	} while (kontrol!=1);
	DosyaYenile.close();
	remove("takim.txt");
	rename("takim.tmp", "takim.txt");
}
void takim::EkleFutbolcu()//TAKIMA FUTBOLCU EKLEME ÝÇÝN
{
	system("CLS");
	ofstream DosyaYaz("takimoyuncu.txt", ios::app);
	string istenentakim;
	int istenenoyuncu;
	int kontrol = 0;
	do
	{
		system("CLS");
		cout << "Oyuncu eklemek istediðiniz takýmýn adýný giriniz : "; cin >> istenentakim;
		ifstream DosyaOkuT("takim.txt");
		while (DosyaOkuT >> takimno >> takimadi >> yoneticiadi >> yoneticisoyadi >> telefon >> adres >> oyuncusayisi)
		{
			if (istenentakim == takimadi)//GÝRÝLEN TAKIM EÞLEÞÝYORSA ÝÞLEME DEVAM EDÝLMESÝ
			{
				kontrol = 2;
				do
				{
					kontrol = 0;
					ifstream DosyaOkuF("futbolcu.txt");
					cout << "Takýma eklemek istediðiniz oyuncunun TC sini giriniz : "; cin >> istenenoyuncu;
					while (DosyaOkuF >> tc >> lisansno >> ad >> soyad >> dogumt >> mevki >> ucreti)
					{
						if (istenenoyuncu == tc)
						{
							DosyaOkuF.close();
							ifstream DosyaOku("takimoyuncu.txt");
							while (DosyaOku >> takimadi >> tc >> ad >> soyad)
							{
								if (istenenoyuncu == tc)//OYUNCU BAÞKA TAKIMDA BULUNUYORSA ÝÞLEMÝN ENGELLENMESÝ
								{
									system("CLS");
									cout << "Seçtiðiniz oyuncu þuanda zaten aktif bir takýmda" << endl;
									cout << "Lütfen baþka bir oyuncu deneyiniz (1) ya da menüye dönünüz (2)" << endl;//1 GÝRÝLÝNCE DÖNGÜ BAÞINA 2 GÝRÝLÝNCE BÜTÜN DÖNGÜLERDEN ÇIKICAK
									cout << "Seçiminiz : "; cin >> kontrol;
									system("CLS");
								}
							}
							DosyaOku.close();
							if (kontrol == 0)//EÐER OYUNCU BAÞAK TAKIMDA BULUNMUYORSA KONTROL=0 KALACAÐINDAN KAYIT ÝÞLEMLERÝNÝN YAPILMASI
							{
								ifstream DosyaOkuT("takim.txt");
								ofstream DosyaYazT("takim.tmp");
								while (DosyaOkuT >> takimno >> takimadi >> yoneticiadi >> yoneticisoyadi >> telefon >> adres >> oyuncusayisi)
								{
									
									ifstream DosyaOkuF("futbolcu.txt");
									if (istenentakim == takimadi)
									{
										oyuncusayisi=oyuncusayisi+1;//OYUNCU SAYISININ ARTTIRILMASI ÝÇÝN SEÇÝLEN TAKIMIN DOSYA KAYDININ YENÝLENMESÝ
										DosyaYazT << takimno << ' ' << takimadi << ' ' << yoneticiadi << ' ' << yoneticisoyadi << ' ' << telefon << ' ' << adres << ' ' << oyuncusayisi << endl;
										
										while (DosyaOkuF >> tc >> lisansno >> ad >> soyad >> dogumt >> mevki >> ucreti)
										{
											if (istenenoyuncu == tc)
											{
												DosyaYaz << takimadi << ' ' << tc << ' ' << ad << ' ' << soyad << endl;
												kontrol = 2;
												system("CLS");
												cout << setw(20) << "*Eklenen bilgiler*" << endl;
												cout << "------------------------" << endl;
												cout << "Takým : " << takimadi << endl;
												cout << "Eklenen oyuncu : " << ad << " " << soyad << endl;
												cout << "TC : " << tc << endl << endl;
											}
										}
									}
									else//DÝÐER TKAIMLARIN DA TEKRARDAN KAYDEDÝLMESÝ ÝÇÝN
										DosyaYazT << takimno << ' ' << takimadi << ' ' << yoneticiadi << ' ' << yoneticisoyadi << ' ' << telefon << ' ' << adres << ' ' << oyuncusayisi << endl;
									DosyaOkuF.close();
								}
								DosyaOkuT.close();
							}
						}
					}
					if (kontrol == 0)//TC BULUNAMAMIÞSA
					{
						cout << "______________________________________________" << endl;
						cout << "|" << setw(46) << "|" << endl;
						cout << "|" << setw(35) << "*GEÇERSÝZ TC NO GÝRDÝNÝZ*" << setw(11) << "|" << endl;
						cout << "|" << setw(46) << "|" << endl;
						cout << "|" << setw(39) << "*LÜTFEN GEÇERLÝ BÝR TC NO GÝRÝNÝZ*" << setw(7) << "|" << endl;
						cout << "|" << setw(46) << "|" << endl;
						cout << "----------------------------------------------" << endl << endl;
					}
					DosyaOkuF.close();
				} while (kontrol != 2);
			}
		}
		if (kontrol == 0)//GÝRÝLEN TAKIMIN BULUNMAMASI
		{
			cout << "______________________________________________" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "|" << setw(35) << "*GEÇERSÝZ TAKIM GÝRDÝNÝZ*" << setw(11) << "|" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "|" << setw(39) << "*LÜTFEN GEÇERLÝ BÝR TAKIM GÝRÝNÝZ*" << setw(7) << "|" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "----------------------------------------------" << endl << endl;
			system("PAUSE");
			system("CLS");
		}
		DosyaOkuT.close();
	} while (kontrol != 2);
	DosyaYaz.close();
	remove("takim.txt");
	rename("takim.tmp", "takim.txt");
}
void takim::SilFutbolcu()
{
	system("CLS");
	int silinecekoyuncu;
	string silinecektakim;
	int kontrol = 0;
	int kontrol2 = 0;
	do
	{
		system("CLS");
		cout << "Oyuncu silmek istediðiniz takýmý giriniz : "; cin >> silinecektakim; cout << endl;
		ifstream DosyaKontrol("takim.txt");
		while (DosyaKontrol >>takimno>> takimadi >> yoneticiadi>> yoneticisoyadi >> telefon>>adres>>oyuncusayisi)
		{
			if (silinecektakim == takimadi)//TAKIMDA OYUNCU BULUNMAMASI DURUMUNDA ÝÞLEMÝN ENGELLENMESÝ
			{
				if (oyuncusayisi == 0)
				{
					kontrol2 = 1;
				}
			}
		}
		if (kontrol2 == 1)
			break;
		DosyaKontrol.close();
		ifstream DosyaOku("takimoyuncu.txt");
		cout << "Takým adý : " << silinecektakim << endl;
		cout << "----------------------" << endl;
		while (DosyaOku >> takimadi >> tc >> ad >> soyad)//SEÇÝLEN TAKIMDA BULUNAN OYUNCULARIN LÝSTELENMESÝ 
		{
			if (silinecektakim == takimadi)
			{
				kontrol = 1;
				cout << "Oyuncu bilgileri :" << tc << "   " << ad << " " << soyad << endl << endl;
			}
		}
		DosyaOku.close();
		if (kontrol == 0)//TAKIM BULUNAMAMIÞSA
		{
			system("CLS");
			cout << "______________________________________________" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "|" << setw(35) << "*GEÇERSÝZ TAKIM GÝRDÝNÝZ*" << setw(11) << "|" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "|" << setw(39) << "*LÜTFEN GEÇERLÝ BÝR TAKIM GÝRÝNÝZ*" << setw(7) << "|" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "----------------------------------------------" << endl << endl;
			system("PAUSE");
		}
	} while (kontrol!=1);
	ifstream DosyaOku("takimoyuncu.txt");
	ofstream DosyaYenile("takimoyuncu.tmp",ios::app);
	kontrol = 0;
	if (kontrol2 == 1)//OYUNCU SAYISI 0 OLAN TAKIMI NBÝLDÝRÝLMESÝ
	{
		cout << "______________________________________________" << endl;
		cout << "|" << setw(46) << "|" << endl;
		cout << "|" << setw(43) << "*BU TAKIMDA HENÜZ OYUNCU BULUNMAMAKTADIR*" << setw(3) << "|" << endl;
		cout << "|" << setw(46) << "|" << endl;
		cout << "|" << setw(42) << "*BAÞARISIZ ÝÞLEM MENÜYE DÖNEBÝLÝRSÝNÝZ*" << setw(4) << "|" << endl;
		cout << "|" << setw(46) << "|" << endl;
		cout << "----------------------------------------------" << endl << endl;
	}
	else//OYUNCULAR LÝSTELENMÝÞSE SÝLMEK ÝSTENEN OYUNCUNUN ALINMASI
	{
		do
		{
			cout << "Silmek istediðiniz oyuncunun TC sini giriniz : "; cin >> silinecekoyuncu; cout << endl;
			while (DosyaOku >> takimadi >> tc >> ad >> soyad)
			{
				if (silinecekoyuncu == tc)
				{
					kontrol = 1;
					ifstream DosyaOku("takim.txt");
					ofstream DosyaYaz("takim.tmp", ios::app);
					while (DosyaOku >> takimno >> takimadi >> yoneticiadi >> yoneticisoyadi >> telefon >> adres >> oyuncusayisi)
					{
						if (silinecektakim == takimadi)
						{
							oyuncusayisi = oyuncusayisi - 1;//OYUNCU SAYISININ AZALTILMASI
							DosyaYaz << takimno << ' ' << takimadi << ' ' << yoneticiadi << ' ' << yoneticisoyadi << ' ' << telefon << ' ' << adres << ' ' << oyuncusayisi << endl;
						}
						else
							DosyaYaz << takimno << ' ' << takimadi << ' ' << yoneticiadi << ' ' << yoneticisoyadi << ' ' << telefon << ' ' << adres << ' ' << oyuncusayisi << endl;
					}
					DosyaOku.close();
					DosyaYaz.close();
					remove("takim.txt");
					rename("takim.tmp", "takim.txt");
				}
				else//DOSYADAKÝ DÝÐER OYUNCULARIN TEKRAR KAYDI
					DosyaYenile << takimadi << ' ' << tc << ' ' << ad << ' ' << soyad << endl;
			}
			if (kontrol == 0)//OYUNCU BULUNAMAMASI DURUMUNDA
			{
				system("CLS");
				cout << "______________________________________________" << endl;
				cout << "|" << setw(46) << "|" << endl;
				cout << "|" << setw(35) << "*GEÇERSÝZ OYUNCU GÝRDÝNÝZ*" << setw(11) << "|" << endl;
				cout << "|" << setw(46) << "|" << endl;
				cout << "|" << setw(39) << "*LÜTFEN GEÇERLÝ BÝR OYUNCU GÝRÝNÝZ*" << setw(7) << "|" << endl;
				cout << "|" << setw(46) << "|" << endl;
				cout << "----------------------------------------------" << endl << endl;
				system("PAUSE");
			}
		} while (kontrol != 1);
	}
	if (kontrol == 1)//ÝÞLEMLERÝN TAMAMLANMASI
	{
		cout << "_______________________________________________" << endl;
		cout << "|" << setw(47) << "|" << endl;
		cout << "|" << setw(42) << "*BAÞARILI ÝÞLEM MENÜYE DÖNEBÝLÝRSÝNÝZ*" << setw(5) << "|" << endl;
		cout << "|" << setw(47) << "|" << endl;
		cout << "-----------------------------------------------" << endl << endl;
	}
	DosyaOku.close();
	DosyaYenile.close();
	remove("takimoyuncu.txt");
	rename("takimoyuncu.tmp", "takimoyuncu.txt");
}
void takim::TakimListele()
{
	system("CLS");
	string takim;
	int kontrol =0 ;
	ifstream DosyaOku("takim.txt");
	while (DosyaOku >> takimno >> takimadi >> yoneticiadi >> yoneticisoyadi >> telefon >> adres >> oyuncusayisi)
	{
		if (oyuncusayisi == 0)//OYUNCUSU OLMAYAN TAKIMIN GÖZÜKMEMESÝ
			break;
		ifstream DosyaOkuTO("takimoyuncu.txt");
		takim = takimadi;
		cout <<endl<<endl<< setw(18) << takim << endl;
		cout << "----------------------------" << endl;
		while (DosyaOkuTO >> takimadi >> tc >> ad >> soyad)
		{
			if (takim == takimadi)
				cout << tc << "   " << ad << " " << soyad << endl;
		}
		DosyaOkuTO.close();
	}
	DosyaOku.close();
	cout << endl << endl;
}
class karsilasma : public takim
{
public:
	int katilantakimsayisi;
	vector <string> takimlar;
	karsilasma() :katilantakimsayisi(0)
	{}

	void KarsilasmadakiTakimlar()
	{
		ifstream DosyaOku("takim.txt");
		while (DosyaOku >> takimno >> takimadi>>yoneticiadi>>yoneticisoyadi>>telefon>>adres>>oyuncusayisi)
		{
			if (oyuncusayisi >= 11)
			{
				katilantakimsayisi = katilantakimsayisi + 1;//YETERLÝ OYUNCUSU BULUNAN TAKIM SAYISININ AYARLANMASI
				takimlar.push_back(takimadi);//YETERLÝ OYUNCUSU BULUNAN TAKIMIN KAYDEDÝLMESÝ
			}
		}
		DosyaOku.close();
	}
	void Karsilasma();
};
void karsilasma :: Karsilasma()
{
	system("CLS");
	int random1=0, random2=0,random3,random4;
	KarsilasmadakiTakimlar();
	
	
	if (katilantakimsayisi < 2)//EN AZ 2 TAKIMIN BUBLUNMASI DURUMU KONTROLÜ
	{
		cout << "______________________________________________" << endl;
		cout << "|" << setw(46) << "|" << endl;
		cout << "|" << setw(35) << "*KARÞILAÞMA ÝÇÝN YETERLÝ*" << setw(11) << "|" << endl;
		cout << "|" << setw(46) << "|" << endl;
		cout << "|" << setw(42) << "*TAKIM BULUNMAMAKTADIR MENÜYE DÖNÜNÜZ*" << setw(4) << "|" << endl;
		cout << "|" << setw(46) << "|" << endl;
		cout << "----------------------------------------------" << endl << endl;
	}
	else
	{
		srand(time(0));
		for (int i = 0; i < katilantakimsayisi; i++)//RASTGELE TAKIM VE PUAN EÞLEÞTÝRMESÝ YAPILMASI
		{
			do
			{
				random1 = rand() % (katilantakimsayisi - 1);//VEKTÖRDEN RASTGELE TAKIM ALINMASI 
				random2 = rand() % (katilantakimsayisi - 1);
			} while (takimlar[random1] == takimlar[random2]);
			random3 = rand() % 5;//PUANIN RASTGELE AYARLANMASI 
			random4 = rand() % 5;
			cout << "________________________________________________" << endl;
			cout << "|" << setw(47) << "|" << endl;
			cout << setw(13) << takimlar[random1] << setw(6) << random3 << setw(5) << "|" << setw(5) << random4 << setw(13) << takimlar[random2] << endl;
			cout << "|" << setw(47) << "|" << endl;
			cout << "------------------------------------------------" << endl << endl;
		}
		cout << "_______________________________________________" << endl;
		cout << "|" << setw(47) << "|" << endl;
		cout << "|" << setw(42) << "*BAÞARILI ÝÞLEM MENÜYE DÖNEBÝLÝRSÝNÝZ*" << setw(5) << "|" << endl;
		cout << "|" << setw(47) << "|" << endl;
		cout << "-----------------------------------------------" << endl << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "Turkish");
	int anamenuislem;//ana menü iþlemleri için
	int oyuncumenuislem;//oyuncu iþlemleri menüsü için
	int takimmenuislem;//takým iþlemleri menüsü için
	futbolcu f;
	takim t;
	karsilasma k;
	do
	{
		system("CLS");
		cout << "________________________________________________" << endl;
		cout << "|" << setw(47) << "|" << endl;
		cout << "|" << setw(29) << "*HOÞGELDÝNÝZ*" << setw(18) << "|" << endl;
		cout << "|" << setw(47) << "|" << endl;
		cout << "|" << setw(40) << "*YAPMAK ÝSTEDÝÐÝNÝZ ÝÞLEMÝ GÝRÝNÝZ*" << setw(7) << "|" << endl;
		cout << "|" << setw(47) << "|" << endl;
		cout << "|" << setw(34) << "[ 1 ] OYUNCU ÝÞLEMLERÝ" << setw(13) << "|" << endl;
		cout << "|" << setw(47) << "|" << endl;
		cout << "|" << setw(33) << "[ 2 ] TAKIM ÝÞLEMLERÝ" << setw(14) << "|" << endl;
		cout << "|" << setw(47) << "|" << endl;
		cout << "|" << setw(31) << "[ 3 ] KARÞILAÞMALAR" << setw(16) << "|" << endl;
		cout << "|" << setw(47) << "|" << endl;
		cout << "|" << setw(23) << "[ 4 ] ÇIKIÞ" << setw(24) << "|" << endl;
		cout << "|" << setw(47) << "|" << endl;
		cout << "------------------------------------------------" << endl << endl;
		cout << setw(28) << "ÝÞLEMÝNÝZ : "; cin >> anamenuislem;
		if (anamenuislem < 1 || anamenuislem>4)//GEÇERSÝZ ÝÞLEM KONTROLÜ
		{
			system("CLS");
			cout << "______________________________________________" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "|" << setw(35) << "*GEÇERSÝZ ÝÞLEM GÝRDÝNÝZ*" << setw(11) << "|" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "|" << setw(37) << "*MENÜYE YÖNLENDÝRÝLÝYORSUNUZ*" << setw(9) << "|" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "----------------------------------------------" << endl << endl;
			system("PAUSE");
		}
		else if (anamenuislem == 1)
		{
			do
			{
				system("CLS");
				cout << "________________________________________________" << endl;
				cout << "|" << setw(47) << "|" << endl;
				cout << "|" << setw(45) << "*YAPMAK ÝSTEDÝÐÝNÝZ OYUNCU ÝÞLEMÝNÝ GÝRÝNÝZ*" << setw(2) << "|" << endl;
				cout << "|" << setw(47) << "|" << endl;
				cout << "|" << setw(31) << "[ 1 ] OYUNCU EKLEME" << setw(16) << "|" << endl;
				cout << "|" << setw(47) << "|" << endl;
				cout << "|" << setw(30) << "[ 2 ] OYUNCU SÝLME" << setw(17) << "|" << endl;
				cout << "|" << setw(47) << "|" << endl;
				cout << "|" << setw(35) << "[ 3 ] OYUNCU GÜNCELLEME" << setw(12) << "|" << endl;
				cout << "|" << setw(47) << "|" << endl;
				cout << "|" << setw(36) << "[ 4 ] OYUNCULARI LÝSTELE" << setw(11) << "|" << endl;
				cout << "|" << setw(47) << "|" << endl;
				cout << "|" << setw(32) << "[ 5 ] ANA MENÜYE DÖN" << setw(15) << "|" << endl;
				cout << "|" << setw(47) << "|" << endl;
				cout << "------------------------------------------------" << endl << endl;
				cout << setw(28) << "ÝÞLEMÝNÝZ : "; cin >> oyuncumenuislem;
				if (oyuncumenuislem < 1 || oyuncumenuislem>5)//GEÇERSÝZ ÝÞLEM KONTROLÜ
				{
					system("CLS");
					cout << "______________________________________________" << endl;
					cout << "|" << setw(46) << "|" << endl;
					cout << "|" << setw(35) << "*GEÇERSÝZ ÝÞLEM GÝRDÝNÝZ*" << setw(11) << "|" << endl;
					cout << "|" << setw(46) << "|" << endl;
					cout << "|" << setw(39) << "*LÜTFEN GEÇERLÝ BÝR ÝÞLEM GÝRÝNÝZ*" << setw(7) << "|" << endl;
					cout << "|" << setw(46) << "|" << endl;
					cout << "----------------------------------------------" << endl << endl;
					system("PAUSE");
				}
				else if (oyuncumenuislem == 1)
				{
					f.FutbolcuKaydet();
					cout << "_______________________________________________" << endl;
					cout << "|" << setw(47) << "|" << endl;
					cout << "|" << setw(42) << "*BAÞARILI ÝÞLEM MENÜYE DÖNEBÝLÝRSÝNÝZ*" << setw(5)<<"|" << endl;
					cout << "|" << setw(47) << "|" << endl;
					cout << "-----------------------------------------------" << endl << endl;
					system("PAUSE");
				}
				else if (oyuncumenuislem == 2) 
				{
					f.FutbolcuSil();
					system("PAUSE");
				}
				else if (oyuncumenuislem == 3) 
				{
					f.FutbolcuGuncelle();
					cout << "_______________________________________________" << endl;
					cout << "|" << setw(47) << "|" << endl;
					cout << "|" << setw(42) << "*BAÞARILI ÝÞLEM MENÜYE DÖNEBÝLÝRSÝNÝZ*" << setw(5) << "|" << endl;
					cout << "|" << setw(47) << "|" << endl;
					cout << "-----------------------------------------------" << endl << endl;
					system("PAUSE");
				}
				else if (oyuncumenuislem == 4)
				{
					f.FutbolculariListele();
					cout << "_______________________________________________" << endl;
					cout << "|" << setw(47) << "|" << endl;
					cout << "|" << setw(42) << "*BAÞARILI ÝÞLEM MENÜYE DÖNEBÝLÝRSÝNÝZ*" << setw(5) << "|" << endl;
					cout << "|" << setw(47) << "|" << endl;
					cout << "-----------------------------------------------" << endl << endl;
					system("PAUSE");
				}
			} while (oyuncumenuislem != 5);
		}
		else if (anamenuislem == 2)
		{
			do
			{
				system("CLS");
				cout << "_________________________________________________" << endl;
				cout << "|" << setw(48) << "|" << endl;
				cout << "|" << setw(45) << "*YAPMAK ÝSTEDÝÐÝNÝZ TAKIM ÝÞLEMÝNÝ GÝRÝNÝZ*" << setw(3) << "|" << endl;
				cout << "|" << setw(48) << "|" << endl;
				cout << "|" << setw(30) << "[ 1 ] TAKIM OLUÞTURMA" << setw(18) << "|" << endl;
				cout << "|" << setw(48) << "|" << endl;
				cout << "|" << setw(26) << "[ 2 ] TAKIM SÝLME" << setw(22) << "|" << endl;
				cout << "|" << setw(48) << "|" << endl;
				cout << "|" << setw(37) << "[ 3 ] TAKIMA FUTBOLCU EKLEME" << setw(11) << "|" << endl;
				cout << "|" << setw(48) << "|" << endl;
				cout << "|" << setw(38) << "[ 4 ] TAKIMDAN FUTBOLCU SÝLME" << setw(10) << "|" << endl;
				cout << "|" << setw(48) << "|" << endl;
				cout << "|" << setw(37) << "[ 5 ] FUTBOLCULARI LÝSTELEME" << setw(11) << "|" << endl;
				cout << "|" << setw(48) << "|" << endl;
				cout << "|" << setw(29) << "[ 6 ] ANA MENÜYE DÖN" << setw(19) << "|" << endl;
				cout << "|" << setw(48) << "|" << endl;
				cout << "-------------------------------------------------" << endl << endl;
				cout << setw(28) << "ÝÞLEMÝNÝZ : "; cin >> takimmenuislem;
				if (takimmenuislem < 1 || takimmenuislem>6)//GEÇERSÝZ ÝÞLEM KONTROLÜ
				{
					system("CLS");
					cout << "______________________________________________" << endl;
					cout << "|" << setw(46) << "|" << endl;
					cout << "|" << setw(35) << "*GEÇERSÝZ ÝÞLEM GÝRDÝNÝZ*" << setw(11) << "|" << endl;
					cout << "|" << setw(46) << "|" << endl;
					cout << "|" << setw(39) << "*LÜTFEN GEÇERLÝ BÝR ÝÞLEM GÝRÝNÝZ*" << setw(7) << "|" << endl;
					cout << "|" << setw(46) << "|" << endl;
					cout << "----------------------------------------------" << endl << endl;
					system("PAUSE");
				}
				else if (takimmenuislem == 1)
				{
					t.TakimOlustur();
					cout << "_______________________________________________" << endl;
					cout << "|" << setw(47) << "|" << endl;
					cout << "|" << setw(42) << "*BAÞARILI ÝÞLEM MENÜYE DÖNEBÝLÝRSÝNÝZ*" << setw(5) << "|" << endl;
					cout << "|" << setw(47) << "|" << endl;
					cout << "-----------------------------------------------" << endl << endl;
					system("PAUSE");
				}
				else if (takimmenuislem == 2)
				{
					t.TakimSil();
					cout << "_______________________________________________" << endl;
					cout << "|" << setw(47) << "|" << endl;
					cout << "|" << setw(42) << "*BAÞARILI ÝÞLEM MENÜYE DÖNEBÝLÝRSÝNÝZ*" << setw(5) << "|" << endl;
					cout << "|" << setw(47) << "|" << endl;
					cout << "-----------------------------------------------" << endl << endl;
					system("PAUSE");
				}
				else if (takimmenuislem == 3) 
				{
					t.EkleFutbolcu();
					cout << "_______________________________________________" << endl;
					cout << "|" << setw(47) << "|" << endl;
					cout << "|" << setw(42) << "*BAÞARILI ÝÞLEM MENÜYE DÖNEBÝLÝRSÝNÝZ*" << setw(5) << "|" << endl;
					cout << "|" << setw(47) << "|" << endl;
					cout << "-----------------------------------------------" << endl << endl;
					system("PAUSE");
				}
				else if (takimmenuislem == 4) 
				{
					t.SilFutbolcu();
					system("PAUSE");
				}
				else if (takimmenuislem == 5)
				{
					t.TakimListele();
					cout << "_______________________________________________" << endl;
					cout << "|" << setw(47) << "|" << endl;
					cout << "|" << setw(42) << "*BAÞARILI ÝÞLEM MENÜYE DÖNEBÝLÝRSÝNÝZ*" << setw(5) << "|" << endl;
					cout << "|" << setw(47) << "|" << endl;
					cout << "-----------------------------------------------" << endl << endl;
					system("PAUSE");
				}
			} while (takimmenuislem != 6);
		}
		else if (anamenuislem == 3)
		 {
			k.Karsilasma();
			system("PAUSE");
		 }
	} while (anamenuislem != 4);
	system("CLS");
	cout << "________________________________________________" << endl;
	cout << "|" << setw(47) << "|" << endl;
	cout << "|" << setw(33) << "*ÝYÝ GÜNLER DÝLERÝZ*" << setw(14) << "|" << endl;
	cout << "|" << setw(47) << "|" << endl;
	cout << "------------------------------------------------" << endl << endl;
	system("PAUSE");
}