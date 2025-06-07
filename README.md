# Vacuum Cleaner Robot with Arduino

Otomatik bir şekilde mesafe ölçümü yapabilen, engelleri tespit edip buna yönelik kaçış manevraları yapabilen ve bu süreç içerisinde vakum yapabilen bir prototip robot projedsiir.

### Malzemeler

•	Ardunio Uno x1
•	H Bridge L298N Motor Sürücüsü x1
•	HC-SR04 Ultrasonic Distance x3
•	Wheels with Micro Gearmotor HPCB (Sarı Uçlu Motor) x2
•	Sarhoş Teker x1
•	Infrared Proximity Sensor(IR Kızılötesi Sensör) x1
•	LM2596 Voltaj Regülatörü x1
•	9V GreenCell Pil x1
•	Mini Breadboard x1
•	Açma/Kapama Anahtar Buton x1
•	12V DC Motor x1

### Devre Diyagramı

![Image](https://github.com/user-attachments/assets/2b398104-1a35-43db-982d-a518ce946835)

## Ardunio Uno ve Kod Hakkında

Robotun yapımında herhangi bir PWM modülüne sahip olmadığımdan dolayı sinyal genişliği fiziksel olarak değiştirelemiyor haliyle de hem vakumun, hem de sarı uçlu tekerlekterin motorları ya tam güç açık olarak çalışıyor ya da direkt kapalı konuma getirilebiliyordu. Projenin başlangıcından itibaren vakumu sabit güçte çalıştırmak istediğimden dolayı vakum kısmı bir problem değildi ancak tekerlekleri dönndüren motorlarımız 250 RPM'de robotun tüm elektronik kutusu ve iskeletini taşırken çok hızlı hareket etmekteydi. Buna çözüm olaraksa normalde Uno kartlar üzerindeki PWM destekli  3-5-6-9-11 gibi pinleri kullanmamız gerekmekte ve C++ tabanlı IDE programı üzerinden yazacağımız kod üzerinde spesifik şekilde sinyal genişliği değiştirebilirdi ancak 3 ultrasonik mesafe sensörünün sensör başına dört pin, güç-ground-triger-echo, gerektiyor oluşu ve IR sensörünün de benzer şekilde üç adet pin gerektiyor oluşu Uno kartının 14 dijital pininin 11 pinini doldurmasına yol açıyordu, matematik hesabının burada karışıklık yaratmaması adına tüm sensörlerin ground ve güç pinleri breadboard üzerinde seri bağlanarak ardunio'ya takıldı. 

Haliyle PWM destekli pinlerin dolu oluşu ve geriye sadece D0 ve D1 ile D13 pinini boş bırakıyor oluşumuzdan dolayı PWM ayarlarını kodumuzdaki SOFTPWM kütüphanesi ile yapılmaktadır. Motor sürücünün iki adet pwm sinyali alabilen pinlerini (enb ve ena) D0 ve D1 pinlerine bağlayarak iki tekere de gereken PWM sinyallerini yazılımsal olarak gönderildi. Bunun düzgün çalışması adına D0 ve D1 pinleri haberleşme adına da kullanıldığından kodun kendisinde Serial Monitörü kullanan herhahngi bir komut satırı bulunmamaktadır.


### Bellek Yönetimi

Proje doğrultusunda yazılan kod Arduino Uno'nun total hafızasının %11'ini (3572 byte) kaplamaktadır. Dinamik belleğinse %9'unu (202 byte) kaplamaktadır. 
