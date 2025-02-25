//***********************************************************************************************************************
//**                                                                                                                   **
//**                                     SAKARYA �N�VERS�TES�                                                          **
//**                          B�LG�SAYAR VE B�L���M B�L�MLER� FAK�LTES�                                                **
//**                                B�LG�SAYAR M�HEND�SL��� B�L�M�                                                     **
//**                                                                                                                   **
//**                                  PROJE NUMARASI..: 1                                                              **
//**                                  ��RENC� ADI.....: SUDE ANDURMAN                                                  **
//**                                  ��RENC� NUMARASI: b231210005                                                     **
//**                                  DERS GRUBU......: A                                                              **
//**                                                                                                                   ** 
//**                                                                                                                   **  
//**                Ama�:Futbol ligi takip sistemi ger�ekle�tiren bir program haz�rlamak                               **
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
		if (tckontrol < 1000 || tckontrol > 9999)//ALINAN TCN�N SINIRLANDIRILMASI
		{
			do
			{
				if (tckontrol < 1000 || tckontrol > 9999)
				{
					cout << "Ge�ersiz TC kimlik numaras� girdiniz l�tfen 4 haneli olmas�na dikkat ediniz." << endl;
					cout << "Futbolcunun tcsi (4 haneli) : "; cin >> tckontrol; cout << endl;
				}
				else
					dongukontrol = 'h';
			} while (dongukontrol != 'h');
		}
		dongukontrol = 'e';
		int sayac = 0;
		do//ALINAN TC N�N D��ER TCLER �LE AYNI OLMAMASI KONTROL� ���N 
		{
			do
			{
				sayac = 0;
				ifstream DosyaOku("futbolcu.txt");
				while (DosyaOku >> tc >> lisansno >> ad >> soyad >> dogumt >> mevki >> ucreti)
				{
					if (tckontrol == tc)
					{
						cout << "Bu TC numaral� ba�ka bir oyuncu bulunmaktad�r l�tfen tekrar giriniz." << endl;
						cout << "Futbolcunun tcsi (4 haneli) : "; cin >> tckontrol; cout << endl;
						if (tckontrol < 1000 || tckontrol > 9999)
						{
							do
							{
								if (tckontrol < 1000 || tckontrol > 9999)
								{
									cout << "Ge�ersiz TC kimlik numaras� girdiniz l�tfen 4 haneli olmas�na dikkat ediniz." << endl;
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
			if (sayac == 0)//B�T�N TCLERLE TEKRAR KAR�ILA�TIRILIP AYNI OLMADI�INDA D�NG�DEN �IKI� ���N 
				dongukontrol = 'h';
		} while (dongukontrol != 'h');
		tc = tckontrol;
		cout << "Futbolcunun lisans numaras� : "; cin >> lisansno; cout << endl;
		cout << "Futbolcunun ad� : "; cin>>ad; cout << endl;
		cout << "Futbolcunun soyad� : "; cin >> soyad; cout << endl;
		cout << "Futbolcunun do�um tarihi (�RN; 2.12.2000) : "; cin >> dogumt; cout << endl;
		cout << "Futbolcunun mevkisi (bo�luk b�rakmadan yaz�n�z) : "; cin >> mevki; cout << endl;
		cout << "Futbolcunun �creti : "; cin >> ucreti; cout << endl;
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
		cout << "Silmek istedi�iniz futbolcunun tc sini giriniz : "; cin >> silinecekoyuncu; cout << endl;
		ifstream DosyaOkuTO("takimoyuncu.txt");
		while (DosyaOkuTO >> takimadi >> tc >> ad >> soyad)//S�L�NMEK �STENEN OYUNCU HERHANG� B�R TAKIMDAYSA ��LEM�N ENGELLENMES�
		{
			if (silinecekoyuncu == tc)
			{
				cout << "Bu oyuncu �uanda aktif bir tak�mda bulunuyor." << endl;
				cout << "L�tfen �nce silmek istedi�iniz oyuncuyu tak�mdan ��kar�n�z. " << endl << endl;
				kontrol = 1;
				cout << "_______________________________________________" << endl;
				cout << "|" << setw(47) << "|" << endl;
				cout << "|" << setw(42) << "*BA�ARISIZ ��LEM MEN�YE D�NEB�L�RS�N�Z*" << setw(5) << "|" << endl;
				cout << "|" << setw(47) << "|" << endl;
				cout << "-----------------------------------------------" << endl << endl;
			}
		}
		if (kontrol == 1)
			break;
		while (DosyaOku >> tc >> lisansno >> ad >> soyad >> dogumt >> mevki >> ucreti)//OYUNCU S�LME ��LEM�N�N YAPILMASI
		{
			if (silinecekoyuncu == tc)
			{
				sayac++;
				cout << setw(20) << "*Silinecek oyuncunun bilgileri*" << endl;
				cout << "---------------------------------------" << endl;
				cout << "Oyuncu : " << ad << " " << soyad << endl;
				cout << "Do�um tarihi : " << dogumt << endl;
				cout << "Lisans No :" << lisansno << endl;
				cout << "Mevki : " << mevki << endl;
				cout << "Ald��� �cret : " << ucreti << endl;
				dongukontrol = 'e';
			}
			else
			{
				DosyaYenile << tc << ' ' << lisansno << ' ' << ad << ' ' << soyad << ' ' << dogumt << ' ' << mevki << ' ' << ucreti << endl;
			}
		}
		if (sayac == 0)//BULUNMAYAN B�R TC G�R�LD���NDE ��LEM�N TEKRARLANMASI
		{
			cout << "______________________________________________" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "|" << setw(35) << "*GE�ERS�Z TC NO G�RD�N�Z*" << setw(11) << "|" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "|" << setw(39) << "*L�TFEN GE�ERL� B�R TC NO G�R�N�Z*" << setw(7) << "|" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "----------------------------------------------" << endl << endl;
			cout << "_______________________________________________" << endl;
			cout << "|" << setw(47) << "|" << endl;
			cout << "|" << setw(42) << "*BA�ARISIZ ��LEM MEN�YE D�NEB�L�RS�N�Z*" << setw(5) << "|" << endl;
			cout << "|" << setw(47) << "|" << endl;
			cout << "-----------------------------------------------" << endl << endl;
			dongukontrol='c';
			
		}
		else if (sayac != 0)
		{
			cout << "_______________________________________________" << endl;
			cout << "|" << setw(47) << "|" << endl;
			cout << "|" << setw(42) << "*BA�ARILI ��LEM MEN�YE D�NEB�L�RS�N�Z*" << setw(5) << "|" << endl;
			cout << "|" << setw(47) << "|" << endl;
			cout << "-----------------------------------------------" << endl << endl;
		}
		DosyaYenile.close();
		DosyaOku.close();
		remove("futbolcu.txt");
		rename("futbolcu.tmp", "futbolcu.txt");//D�NG� ���NE YAZMA NEDEN� VAR...
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
	cout << "G�ncellemek istedi�iniz oyuncunun TC sini giriniz."; cin >> guncellenecekoyuncu; cout << endl;
	while (DosyaOku >> tc >> lisansno >> ad >> soyad >> dogumt >> mevki >> ucreti)
	{
		if (guncellenecekoyuncu == tc)
		{
			cout << setw(20) << "*G�ncellenecek oyuncunun bilgileri*" << endl;
			cout << "---------------------------------------" << endl;
			cout << "Oyuncu : " << ad << " " << soyad << endl;
			cout << "Do�um tarihi : " << dogumt << endl;
			cout << "Lisans No :" << lisansno << endl;
			cout << "TC : " << tc << endl;
			cout << "Mevki : " << mevki << endl;
			cout << "Ald��� �cret : " << ucreti << endl;
			cout << "---------------------------------------" << endl << endl;
			cout << setw(20) << "*G�ncel bilgileri giriniz*" << endl;
			cout << "TC (4 haneli) : "; cin >> tckontrol;
			if (tckontrol < 1000 || tckontrol > 9999)//TC SINIRLAMASIKONTROL�
			{
				do
				{
					if (tckontrol < 1000 || tckontrol > 9999)
					{
						cout << "Ge�ersiz TC kimlik numaras� girdiniz l�tfen 4 haneli olmas�na dikkat ediniz." << endl;
						cout << "Futbolcunun tcsi (4 haneli) : "; cin >> tckontrol; cout << endl;
					}
					else
						dongukontrol = 'h';
				} while (dongukontrol != 'h');
			}
			dongukontrol = 'e';
			int sayac = 0;
			do//ALINAN YEN� TCN�N TEKRARDAN D��ERLER�YLE AYNI OLUP OLMAMA KONTROL�N�N YAPILMASI
			{
				do
				{
					sayac = 0;
					ifstream DosyaOku("futbolcu.txt");
					while (DosyaOku >> tc >> lisansno >> ad >> soyad >> dogumt >> mevki >> ucreti)
					{
						if (tckontrol == tc)
						{
							cout << "Bu TC numaral� ba�ka bir oyuncu bulunmaktad�r l�tfen tekrar giriniz." << endl;
							cout << "Futbolcunun tcsi (4 haneli) : "; cin >> tckontrol; cout << endl;
							if (tckontrol < 1000 || tckontrol > 9999)
							{
								do
								{
									if (tckontrol < 1000 || tckontrol > 9999)
									{
										cout << "Ge�ersiz TC kimlik numaras� girdiniz l�tfen 4 haneli olmas�na dikkat ediniz." << endl;
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
				if (sayac == 0)//B�T�N TCLERLE KAR�ILA�TIRMA B�TT�KTEN SONRA AYNI OLMADIYSA D�NG�DEN �IKI� ���N 
					dongukontrol = 'h';
			} while (dongukontrol != 'h');
			tc = tckontrol;
			cout << "Lisans No : "; cin >> lisansno;
			cout << "Ad : "; cin >> ad;
			cout << "Soyad : "; cin >> soyad;
			cout << "Do�um tarihi (1/2/2000) : "; cin >> dogumt;
			cout << "Mevki : "; cin >> mevki;
			cout << "�cret : "; cin >> ucreti;
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
		cout << "Do�um tarihi : " << dogumt << endl;
		cout << "TC : " << tc << endl;
		cout << "Lisans NO : " << lisansno << endl;
		cout << "Mevki : " << mevki << endl;
		cout << "�creti : " << ucreti << endl;
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
	
	void TakimAl()//TAKIM EKLEMEK ���N
	{
		static int takimnobelirleme=1;
		system("CLS");
		string takimadkontrol;
		char dongukontrol = 'e';
		int kontrol=0;
		ifstream DosyaOku("takim.txt");
		while (DosyaOku >> takimno >> takimadi >> yoneticiadi >> yoneticisoyadi >> telefon >> adres >> oyuncusayisi)
		{
			if (takimnobelirleme == takimno)//TAKIM EKLEND���NDE TAKIM NUMARASININ SIRAYA G�RE BEL�RLENMES� 
				takimnobelirleme++;
		}
		DosyaOku.close();
		do
		{
			cout << "Tak�m ad� : "; cin >> takimadkontrol;
			do
			{
				kontrol = 0;
				ifstream DosyaOku("takim.txt");
				while (DosyaOku >> takimno >> takimadi >> yoneticiadi >> yoneticisoyadi >> telefon >> adres >> oyuncusayisi)
				{
					if (takimadkontrol == takimadi)//AYNI TAKIM ADININ KULLANILMASININ ENGELLENMES�
					{
						cout << endl<<"Kullan�lan bir tak�m ad�n� tekrardan kullanamazs�n�z " << endl;
						cout << "L�tfen ba�ka bir ismi giriniz" << endl<<endl;
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
		cout << "Y�netici ad� : "; cin >> yoneticiadi;
		cout << "Y�netici soyad� : "; cin >> yoneticisoyadi;
		cout << "Telefon numaras� : "; cin >> telefon;
		cout << "Adres : "; cin >> adres;
	}
	void TakimOlustur();
	void TakimSil();
	void EkleFutbolcu();
	void SilFutbolcu();
	void TakimListele();
};
void takim::TakimOlustur()//TAKIM EKLEM ��LEM�N�N TAMAMLANMASI
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
		cout << "Silmek istedi�iniz tak�m� giriniz : "; cin >> silinecektakim; cout << endl;
		ifstream DosyaOku("takim.txt");
		while (DosyaOku >> takimno >> takimadi >> yoneticiadi >> yoneticisoyadi >> telefon >> adres >> oyuncusayisi)
		{
			if (silinecektakim == takimadi)
			{
				kontrol=1;
				cout <<setw(20) <<"*Silinecek tak�m�n bilgileri*" << endl;
				cout << "Tak�m numaras� : " << takimno<<endl;
				cout << "Tak�m ad� : " << takimadi<<endl;
				cout << "Tak�m y�neticisi : " << yoneticiadi << " " << yoneticisoyadi << endl;
				cout << "Telefon : " << telefon << endl;
				cout << "Adres : " << adres << endl;
				cout << "Oyuncu sayisi : " << oyuncusayisi << endl;
				ifstream DosyaOkuTO("takimoyuncu.txt");
				ofstream DosyaYenile("takimoyuncu.tmp",ios::app);
				string takimadiTO;
				while (DosyaOkuTO >> takimadiTO >> tc >> ad >> soyad)//TAKIM S�L�N�NCE ���NDE BULUNAN OYUNCULARINDA TAKIMDAK� OYUNCULAR DOSYASINDAN S�L�NMES�
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
			else//TAKIM S�L�ND�KTEN SONRA DOSYANIN YEN�LENMES�
			{
				DosyaYenile << takimno << ' ' << takimadi << ' ' << yoneticiadi << ' ' << yoneticisoyadi << ' ' << telefon << ' ' << adres << ' ' << oyuncusayisi << endl;
			}
		}
		DosyaOku.close();
		if (kontrol == 0)//G�R�LEN TAKIMIN BULUNMAMASI DURUMU ���N
		{
			cout << "______________________________________________" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "|" << setw(35) << "*GE�ERS�Z TAKIM G�RD�N�Z*" << setw(11) << "|" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "|" << setw(39) << "*L�TFEN GE�ERL� B�R TAKIM G�R�N�Z*" << setw(7) << "|" << endl;
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
void takim::EkleFutbolcu()//TAKIMA FUTBOLCU EKLEME ���N
{
	system("CLS");
	ofstream DosyaYaz("takimoyuncu.txt", ios::app);
	string istenentakim;
	int istenenoyuncu;
	int kontrol = 0;
	do
	{
		system("CLS");
		cout << "Oyuncu eklemek istedi�iniz tak�m�n ad�n� giriniz : "; cin >> istenentakim;
		ifstream DosyaOkuT("takim.txt");
		while (DosyaOkuT >> takimno >> takimadi >> yoneticiadi >> yoneticisoyadi >> telefon >> adres >> oyuncusayisi)
		{
			if (istenentakim == takimadi)//G�R�LEN TAKIM E�LE��YORSA ��LEME DEVAM ED�LMES�
			{
				kontrol = 2;
				do
				{
					kontrol = 0;
					ifstream DosyaOkuF("futbolcu.txt");
					cout << "Tak�ma eklemek istedi�iniz oyuncunun TC sini giriniz : "; cin >> istenenoyuncu;
					while (DosyaOkuF >> tc >> lisansno >> ad >> soyad >> dogumt >> mevki >> ucreti)
					{
						if (istenenoyuncu == tc)
						{
							DosyaOkuF.close();
							ifstream DosyaOku("takimoyuncu.txt");
							while (DosyaOku >> takimadi >> tc >> ad >> soyad)
							{
								if (istenenoyuncu == tc)//OYUNCU BA�KA TAKIMDA BULUNUYORSA ��LEM�N ENGELLENMES�
								{
									system("CLS");
									cout << "Se�ti�iniz oyuncu �uanda zaten aktif bir tak�mda" << endl;
									cout << "L�tfen ba�ka bir oyuncu deneyiniz (1) ya da men�ye d�n�n�z (2)" << endl;//1 G�R�L�NCE D�NG� BA�INA 2 G�R�L�NCE B�T�N D�NG�LERDEN �IKICAK
									cout << "Se�iminiz : "; cin >> kontrol;
									system("CLS");
								}
							}
							DosyaOku.close();
							if (kontrol == 0)//E�ER OYUNCU BA�AK TAKIMDA BULUNMUYORSA KONTROL=0 KALACA�INDAN KAYIT ��LEMLER�N�N YAPILMASI
							{
								ifstream DosyaOkuT("takim.txt");
								ofstream DosyaYazT("takim.tmp");
								while (DosyaOkuT >> takimno >> takimadi >> yoneticiadi >> yoneticisoyadi >> telefon >> adres >> oyuncusayisi)
								{
									
									ifstream DosyaOkuF("futbolcu.txt");
									if (istenentakim == takimadi)
									{
										oyuncusayisi=oyuncusayisi+1;//OYUNCU SAYISININ ARTTIRILMASI ���N SE��LEN TAKIMIN DOSYA KAYDININ YEN�LENMES�
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
												cout << "Tak�m : " << takimadi << endl;
												cout << "Eklenen oyuncu : " << ad << " " << soyad << endl;
												cout << "TC : " << tc << endl << endl;
											}
										}
									}
									else//D��ER TKAIMLARIN DA TEKRARDAN KAYDED�LMES� ���N
										DosyaYazT << takimno << ' ' << takimadi << ' ' << yoneticiadi << ' ' << yoneticisoyadi << ' ' << telefon << ' ' << adres << ' ' << oyuncusayisi << endl;
									DosyaOkuF.close();
								}
								DosyaOkuT.close();
							}
						}
					}
					if (kontrol == 0)//TC BULUNAMAMI�SA
					{
						cout << "______________________________________________" << endl;
						cout << "|" << setw(46) << "|" << endl;
						cout << "|" << setw(35) << "*GE�ERS�Z TC NO G�RD�N�Z*" << setw(11) << "|" << endl;
						cout << "|" << setw(46) << "|" << endl;
						cout << "|" << setw(39) << "*L�TFEN GE�ERL� B�R TC NO G�R�N�Z*" << setw(7) << "|" << endl;
						cout << "|" << setw(46) << "|" << endl;
						cout << "----------------------------------------------" << endl << endl;
					}
					DosyaOkuF.close();
				} while (kontrol != 2);
			}
		}
		if (kontrol == 0)//G�R�LEN TAKIMIN BULUNMAMASI
		{
			cout << "______________________________________________" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "|" << setw(35) << "*GE�ERS�Z TAKIM G�RD�N�Z*" << setw(11) << "|" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "|" << setw(39) << "*L�TFEN GE�ERL� B�R TAKIM G�R�N�Z*" << setw(7) << "|" << endl;
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
		cout << "Oyuncu silmek istedi�iniz tak�m� giriniz : "; cin >> silinecektakim; cout << endl;
		ifstream DosyaKontrol("takim.txt");
		while (DosyaKontrol >>takimno>> takimadi >> yoneticiadi>> yoneticisoyadi >> telefon>>adres>>oyuncusayisi)
		{
			if (silinecektakim == takimadi)//TAKIMDA OYUNCU BULUNMAMASI DURUMUNDA ��LEM�N ENGELLENMES�
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
		cout << "Tak�m ad� : " << silinecektakim << endl;
		cout << "----------------------" << endl;
		while (DosyaOku >> takimadi >> tc >> ad >> soyad)//SE��LEN TAKIMDA BULUNAN OYUNCULARIN L�STELENMES� 
		{
			if (silinecektakim == takimadi)
			{
				kontrol = 1;
				cout << "Oyuncu bilgileri :" << tc << "   " << ad << " " << soyad << endl << endl;
			}
		}
		DosyaOku.close();
		if (kontrol == 0)//TAKIM BULUNAMAMI�SA
		{
			system("CLS");
			cout << "______________________________________________" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "|" << setw(35) << "*GE�ERS�Z TAKIM G�RD�N�Z*" << setw(11) << "|" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "|" << setw(39) << "*L�TFEN GE�ERL� B�R TAKIM G�R�N�Z*" << setw(7) << "|" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "----------------------------------------------" << endl << endl;
			system("PAUSE");
		}
	} while (kontrol!=1);
	ifstream DosyaOku("takimoyuncu.txt");
	ofstream DosyaYenile("takimoyuncu.tmp",ios::app);
	kontrol = 0;
	if (kontrol2 == 1)//OYUNCU SAYISI 0 OLAN TAKIMI NB�LD�R�LMES�
	{
		cout << "______________________________________________" << endl;
		cout << "|" << setw(46) << "|" << endl;
		cout << "|" << setw(43) << "*BU TAKIMDA HEN�Z OYUNCU BULUNMAMAKTADIR*" << setw(3) << "|" << endl;
		cout << "|" << setw(46) << "|" << endl;
		cout << "|" << setw(42) << "*BA�ARISIZ ��LEM MEN�YE D�NEB�L�RS�N�Z*" << setw(4) << "|" << endl;
		cout << "|" << setw(46) << "|" << endl;
		cout << "----------------------------------------------" << endl << endl;
	}
	else//OYUNCULAR L�STELENM��SE S�LMEK �STENEN OYUNCUNUN ALINMASI
	{
		do
		{
			cout << "Silmek istedi�iniz oyuncunun TC sini giriniz : "; cin >> silinecekoyuncu; cout << endl;
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
				else//DOSYADAK� D��ER OYUNCULARIN TEKRAR KAYDI
					DosyaYenile << takimadi << ' ' << tc << ' ' << ad << ' ' << soyad << endl;
			}
			if (kontrol == 0)//OYUNCU BULUNAMAMASI DURUMUNDA
			{
				system("CLS");
				cout << "______________________________________________" << endl;
				cout << "|" << setw(46) << "|" << endl;
				cout << "|" << setw(35) << "*GE�ERS�Z OYUNCU G�RD�N�Z*" << setw(11) << "|" << endl;
				cout << "|" << setw(46) << "|" << endl;
				cout << "|" << setw(39) << "*L�TFEN GE�ERL� B�R OYUNCU G�R�N�Z*" << setw(7) << "|" << endl;
				cout << "|" << setw(46) << "|" << endl;
				cout << "----------------------------------------------" << endl << endl;
				system("PAUSE");
			}
		} while (kontrol != 1);
	}
	if (kontrol == 1)//��LEMLER�N TAMAMLANMASI
	{
		cout << "_______________________________________________" << endl;
		cout << "|" << setw(47) << "|" << endl;
		cout << "|" << setw(42) << "*BA�ARILI ��LEM MEN�YE D�NEB�L�RS�N�Z*" << setw(5) << "|" << endl;
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
		if (oyuncusayisi == 0)//OYUNCUSU OLMAYAN TAKIMIN G�Z�KMEMES�
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
				katilantakimsayisi = katilantakimsayisi + 1;//YETERL� OYUNCUSU BULUNAN TAKIM SAYISININ AYARLANMASI
				takimlar.push_back(takimadi);//YETERL� OYUNCUSU BULUNAN TAKIMIN KAYDED�LMES�
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
	
	
	if (katilantakimsayisi < 2)//EN AZ 2 TAKIMIN BUBLUNMASI DURUMU KONTROL�
	{
		cout << "______________________________________________" << endl;
		cout << "|" << setw(46) << "|" << endl;
		cout << "|" << setw(35) << "*KAR�ILA�MA ���N YETERL�*" << setw(11) << "|" << endl;
		cout << "|" << setw(46) << "|" << endl;
		cout << "|" << setw(42) << "*TAKIM BULUNMAMAKTADIR MEN�YE D�N�N�Z*" << setw(4) << "|" << endl;
		cout << "|" << setw(46) << "|" << endl;
		cout << "----------------------------------------------" << endl << endl;
	}
	else
	{
		srand(time(0));
		for (int i = 0; i < katilantakimsayisi; i++)//RASTGELE TAKIM VE PUAN E�LE�T�RMES� YAPILMASI
		{
			do
			{
				random1 = rand() % (katilantakimsayisi - 1);//VEKT�RDEN RASTGELE TAKIM ALINMASI 
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
		cout << "|" << setw(42) << "*BA�ARILI ��LEM MEN�YE D�NEB�L�RS�N�Z*" << setw(5) << "|" << endl;
		cout << "|" << setw(47) << "|" << endl;
		cout << "-----------------------------------------------" << endl << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "Turkish");
	int anamenuislem;//ana men� i�lemleri i�in
	int oyuncumenuislem;//oyuncu i�lemleri men�s� i�in
	int takimmenuislem;//tak�m i�lemleri men�s� i�in
	futbolcu f;
	takim t;
	karsilasma k;
	do
	{
		system("CLS");
		cout << "________________________________________________" << endl;
		cout << "|" << setw(47) << "|" << endl;
		cout << "|" << setw(29) << "*HO�GELD�N�Z*" << setw(18) << "|" << endl;
		cout << "|" << setw(47) << "|" << endl;
		cout << "|" << setw(40) << "*YAPMAK �STED���N�Z ��LEM� G�R�N�Z*" << setw(7) << "|" << endl;
		cout << "|" << setw(47) << "|" << endl;
		cout << "|" << setw(34) << "[ 1 ] OYUNCU ��LEMLER�" << setw(13) << "|" << endl;
		cout << "|" << setw(47) << "|" << endl;
		cout << "|" << setw(33) << "[ 2 ] TAKIM ��LEMLER�" << setw(14) << "|" << endl;
		cout << "|" << setw(47) << "|" << endl;
		cout << "|" << setw(31) << "[ 3 ] KAR�ILA�MALAR" << setw(16) << "|" << endl;
		cout << "|" << setw(47) << "|" << endl;
		cout << "|" << setw(23) << "[ 4 ] �IKI�" << setw(24) << "|" << endl;
		cout << "|" << setw(47) << "|" << endl;
		cout << "------------------------------------------------" << endl << endl;
		cout << setw(28) << "��LEM�N�Z : "; cin >> anamenuislem;
		if (anamenuislem < 1 || anamenuislem>4)//GE�ERS�Z ��LEM KONTROL�
		{
			system("CLS");
			cout << "______________________________________________" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "|" << setw(35) << "*GE�ERS�Z ��LEM G�RD�N�Z*" << setw(11) << "|" << endl;
			cout << "|" << setw(46) << "|" << endl;
			cout << "|" << setw(37) << "*MEN�YE Y�NLEND�R�L�YORSUNUZ*" << setw(9) << "|" << endl;
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
				cout << "|" << setw(45) << "*YAPMAK �STED���N�Z OYUNCU ��LEM�N� G�R�N�Z*" << setw(2) << "|" << endl;
				cout << "|" << setw(47) << "|" << endl;
				cout << "|" << setw(31) << "[ 1 ] OYUNCU EKLEME" << setw(16) << "|" << endl;
				cout << "|" << setw(47) << "|" << endl;
				cout << "|" << setw(30) << "[ 2 ] OYUNCU S�LME" << setw(17) << "|" << endl;
				cout << "|" << setw(47) << "|" << endl;
				cout << "|" << setw(35) << "[ 3 ] OYUNCU G�NCELLEME" << setw(12) << "|" << endl;
				cout << "|" << setw(47) << "|" << endl;
				cout << "|" << setw(36) << "[ 4 ] OYUNCULARI L�STELE" << setw(11) << "|" << endl;
				cout << "|" << setw(47) << "|" << endl;
				cout << "|" << setw(32) << "[ 5 ] ANA MEN�YE D�N" << setw(15) << "|" << endl;
				cout << "|" << setw(47) << "|" << endl;
				cout << "------------------------------------------------" << endl << endl;
				cout << setw(28) << "��LEM�N�Z : "; cin >> oyuncumenuislem;
				if (oyuncumenuislem < 1 || oyuncumenuislem>5)//GE�ERS�Z ��LEM KONTROL�
				{
					system("CLS");
					cout << "______________________________________________" << endl;
					cout << "|" << setw(46) << "|" << endl;
					cout << "|" << setw(35) << "*GE�ERS�Z ��LEM G�RD�N�Z*" << setw(11) << "|" << endl;
					cout << "|" << setw(46) << "|" << endl;
					cout << "|" << setw(39) << "*L�TFEN GE�ERL� B�R ��LEM G�R�N�Z*" << setw(7) << "|" << endl;
					cout << "|" << setw(46) << "|" << endl;
					cout << "----------------------------------------------" << endl << endl;
					system("PAUSE");
				}
				else if (oyuncumenuislem == 1)
				{
					f.FutbolcuKaydet();
					cout << "_______________________________________________" << endl;
					cout << "|" << setw(47) << "|" << endl;
					cout << "|" << setw(42) << "*BA�ARILI ��LEM MEN�YE D�NEB�L�RS�N�Z*" << setw(5)<<"|" << endl;
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
					cout << "|" << setw(42) << "*BA�ARILI ��LEM MEN�YE D�NEB�L�RS�N�Z*" << setw(5) << "|" << endl;
					cout << "|" << setw(47) << "|" << endl;
					cout << "-----------------------------------------------" << endl << endl;
					system("PAUSE");
				}
				else if (oyuncumenuislem == 4)
				{
					f.FutbolculariListele();
					cout << "_______________________________________________" << endl;
					cout << "|" << setw(47) << "|" << endl;
					cout << "|" << setw(42) << "*BA�ARILI ��LEM MEN�YE D�NEB�L�RS�N�Z*" << setw(5) << "|" << endl;
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
				cout << "|" << setw(45) << "*YAPMAK �STED���N�Z TAKIM ��LEM�N� G�R�N�Z*" << setw(3) << "|" << endl;
				cout << "|" << setw(48) << "|" << endl;
				cout << "|" << setw(30) << "[ 1 ] TAKIM OLU�TURMA" << setw(18) << "|" << endl;
				cout << "|" << setw(48) << "|" << endl;
				cout << "|" << setw(26) << "[ 2 ] TAKIM S�LME" << setw(22) << "|" << endl;
				cout << "|" << setw(48) << "|" << endl;
				cout << "|" << setw(37) << "[ 3 ] TAKIMA FUTBOLCU EKLEME" << setw(11) << "|" << endl;
				cout << "|" << setw(48) << "|" << endl;
				cout << "|" << setw(38) << "[ 4 ] TAKIMDAN FUTBOLCU S�LME" << setw(10) << "|" << endl;
				cout << "|" << setw(48) << "|" << endl;
				cout << "|" << setw(37) << "[ 5 ] FUTBOLCULARI L�STELEME" << setw(11) << "|" << endl;
				cout << "|" << setw(48) << "|" << endl;
				cout << "|" << setw(29) << "[ 6 ] ANA MEN�YE D�N" << setw(19) << "|" << endl;
				cout << "|" << setw(48) << "|" << endl;
				cout << "-------------------------------------------------" << endl << endl;
				cout << setw(28) << "��LEM�N�Z : "; cin >> takimmenuislem;
				if (takimmenuislem < 1 || takimmenuislem>6)//GE�ERS�Z ��LEM KONTROL�
				{
					system("CLS");
					cout << "______________________________________________" << endl;
					cout << "|" << setw(46) << "|" << endl;
					cout << "|" << setw(35) << "*GE�ERS�Z ��LEM G�RD�N�Z*" << setw(11) << "|" << endl;
					cout << "|" << setw(46) << "|" << endl;
					cout << "|" << setw(39) << "*L�TFEN GE�ERL� B�R ��LEM G�R�N�Z*" << setw(7) << "|" << endl;
					cout << "|" << setw(46) << "|" << endl;
					cout << "----------------------------------------------" << endl << endl;
					system("PAUSE");
				}
				else if (takimmenuislem == 1)
				{
					t.TakimOlustur();
					cout << "_______________________________________________" << endl;
					cout << "|" << setw(47) << "|" << endl;
					cout << "|" << setw(42) << "*BA�ARILI ��LEM MEN�YE D�NEB�L�RS�N�Z*" << setw(5) << "|" << endl;
					cout << "|" << setw(47) << "|" << endl;
					cout << "-----------------------------------------------" << endl << endl;
					system("PAUSE");
				}
				else if (takimmenuislem == 2)
				{
					t.TakimSil();
					cout << "_______________________________________________" << endl;
					cout << "|" << setw(47) << "|" << endl;
					cout << "|" << setw(42) << "*BA�ARILI ��LEM MEN�YE D�NEB�L�RS�N�Z*" << setw(5) << "|" << endl;
					cout << "|" << setw(47) << "|" << endl;
					cout << "-----------------------------------------------" << endl << endl;
					system("PAUSE");
				}
				else if (takimmenuislem == 3) 
				{
					t.EkleFutbolcu();
					cout << "_______________________________________________" << endl;
					cout << "|" << setw(47) << "|" << endl;
					cout << "|" << setw(42) << "*BA�ARILI ��LEM MEN�YE D�NEB�L�RS�N�Z*" << setw(5) << "|" << endl;
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
					cout << "|" << setw(42) << "*BA�ARILI ��LEM MEN�YE D�NEB�L�RS�N�Z*" << setw(5) << "|" << endl;
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
	cout << "|" << setw(33) << "*�Y� G�NLER D�LER�Z*" << setw(14) << "|" << endl;
	cout << "|" << setw(47) << "|" << endl;
	cout << "------------------------------------------------" << endl << endl;
	system("PAUSE");
}