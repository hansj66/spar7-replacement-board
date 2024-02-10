(Norwegian only)
# Spar7 erstatningskort

## Bakgrunn

Dette er siste revisjon av det som i utgangspunktet var et "voksenopplæringsprosjekt" for mange, mange år siden. Dvs jeg ønsket den gang å lære meg å programmere mikrokontrollere, samt gjøre enkle PCB design. Skjema, utlegg og kode bærer preg av dette. Jeg hadde tilgang til en defekt Spar7 og dette var et perfekt prosjekt å bryne seg på.


Siste versjon av kortet er fra 2013 (v6). Siste versjon av firmware er v7.

## Lisens

Firmware og CAD-filer i dette repositoryet er tilgjengelig under [CC BY-NC 4.0](https://creativecommons.org/licenses/by-nc/4.0/) lisens.

## Innhold

* [Firmware](Firmware) - Inneholder programvare. Kildekoden er laget i Atmel Studio 7. Her ligger også hex-fil for siste versjon. Det er ingen programmeringsheader på kortet, så mikrokontrolleren må flashes før montering. Dette kan gjøres med en hvilken som helst ISP programmerer. Chippen kan monteres på et breadboard og gis 5V. Deretter programmeres med f.eks en [AVRISP MKII](https://www.microchip.com/en-us/development-tool/atavrisp2)

* [Target3001](Target3001) - Inneholder Target3001-prosjektfila. Skjema og utlegg er såpass enkelt at dette er trivielt oversettbart til Eks. Eagle, KiCAD eller annet. Target3001 kan evt lastes ned [herfra](https://ibfriedrich.com/en/index.html). (Jeg har ikke forsøkt å åpne dette prosjektet i nyere versjoner av Target)

* [Schematic](Schematic) - Inneholder en PDF av skjema (amatørkveld, men bør være lesbart :)

* [Layout](Layout) - Inneholder en PDF av utlegg (amatørkveld, men bør være lesbart :)

* [Gerber](Gerber) - Inneholder CAM-filene. Disse kan lastes rett opp til en PCB-leverandør, som f.eks [JLCPCB](https://jlcpcb.com/). Disse sender med DHL og du har som regel kortene i hende etter en liten uke. Du må påregne momsfaktura fra DHL i bakkant.

* [Bill of Materials](bill_of_materials.pdf) - Komponentliste, med DigiKey delenummer og estimert pris pr 10.02.2024.


## LES DETTE FØR DU BEGYNNER!

Kantkonnektoren i spillet har signalbaner, 220VAC og 18VAC kant i kant. Hvis du ikke er kvalifisert for å jobbe med nettspenning, så styr unna dette prosjektet. 220V nettspenning kan drepe, eller gi deg et kraftig sjokk.

Dette er også amatørelektronikk. Dvs det er ingen garanti for at ikke kortet tar fyr og brenner ned huset ditt. Just sayin'

## Installasjon

1. Trekk ut kontakten til automaten.
1. Trekk ut det gamle kortet fra edge-connectoren og trekk også evt ut IDC-connectoren, som går til displayet, hvis du har en variant med displaysiffer (Ikke alle automatene, som kortet fungerer i, har dette)
1. Anta at pinnenummereringen på edgeconnectoren starter nærmest hopperen. Pinnen lengst til høyre (nærmest hopperen) er pinne nummer 1. Sjekk at transformatoren i kabinettet ikke er defekt ved å sette i strømkontakten uten noe kort i og sjekk følgende:  
    1. 18VAC mellom pinne 1 og 2  
    1.  220-230VAC (nettspenning) mellom pinne 5 og 6
    1. (med en pinne mot jord). Mål resten av pinnene. Du skal ikke kunne detektere vekselspenning eller likespenning mellom jord og pinne 3,8,9,19,11,12 eller 13. Hvis kortet likevel installeres, så vil dette ødelegges.
1. Koble fra strømmen igjen og sett inn erstatningskortet. Koble evt displayconnectoren til det nye kortet. Displayconnectoren på de gamle Spar7’ene har ikke noen key, så det er mulig å sette inn denne feil vei. (Koble ut strømmen og snu connectoren hvis displayet ikke lyser)
1. Sjekk at begge lysdiodene lyser. Hvis en eller begge av disse er mørke, så er er det sannsynligvis feil ved transformatoren i automaten. Alternativt, så kan det skyldes korrosjon / oksidasjon av edgeconnectoren som kortet er montert i.

![kort](pictures/kort.png)

## Initiell test

1. Åpne knipsekassa og gjenta følgende for hver gevinstport:
1. Aktiver bryteren på baksiden av gevinstporten. Sjekk at gevinst vises i displayet.. Du vil høre at hopper-releet slår inn, slik at bremsen på hoppermotoren kobles fra. Hopperen skal nå begynne å rotere. Gevinst i displayet teller ned med en, inntil hele gevinsten er utbetalt.

![gevinstbryter](pictures/gevinstport.png)

## Generell feilsøking i Spar7

### Hvis en bryter ikke lar seg aktivere

Bryteren kan være defekt, eller det kan ha oppstått kabelbrudd mellom bryteren og edgeconnectoren, Pinnene på edgeconnectoren, som kortet er montert i kan også være korrodert / oksidert.

Bryterne kan testes manuelt hvis kortet trekkes ut av knipsekassa (med strømmen av).

Bryteren kan med et multimeter med kontinuitetssjekk. Bryterne kan ha både NC (Normally closed) og NO (Normally open) tilkoblinger. En defekt bryter kan feile ved at NC-tilkoblingen ikke er lukket når bryteren er i hvilestilling, eller ved at NO-tilkoblingen ikke lukkes når bryteren er aktiv. Vippearmen på bryteren kan også være deformert eller knekt.

De to nederste pinnene på bryterne ved gevinstportene er NC og øverste + nederste pinne er NO. Ledningsbrudd kan finnes ved å måle kontinuitet mellom nederste pinne på gevinstporten og pinne#3 fra venstre på edgeconnectoren.

### Hvis hopperen ikke roterer (ingen mynter utbetales)

Hoppermotoren i knipsekassene er alltid aktiv, men en bremse på motoren sørger for at den kun roterer når gevinst skal utbetales.

Følgende kan forhindre at hopperen fungerer som den skal:

1. Transformatoren leverer ikke strøm til hoppermotoren (NB! nettspenning).
1. Elektromagneten, som frikobler bremsen fungerer ikke. Motoren må isåfall repareres eller erstattes.
1. Coin-røret over hopperen er montert slik at det er i kontakt med rotoren og derfor bremser hopperen. Skru coin-røret litt opp for å korrigere dette.
1. Rotoren er skitten. Myntene er i konstant kontakt med rotoren, og det vil kunne avsettes støv/fett på denne. Dette fikses ved å demontere og vaske de hvite plastdelene.
1. Fjærene på bremsen til motoren mangler, eller har brukket.

### Hvis hopperen roterer svært sakte, eller starter sakte

Hvis pkt 3 og 4 i avsnittet over er ok, så kan dette skyldes seig olje i giret på motoren. Hele hopper-mekanismen må da kobles fra spillet og demonteres. Gammelt fett og seig olje kan fjernes med white sprite eller lignende.

NB! Vær svært forsiktig når du løsner myntplata fra akslingen, slik at denne ikke knekker.

### Hvis spillet utbetaler 7-gevinst på gevinstport 2,3 eller 4.

Gevinstbryteren er defekt (Se forslag til erstatningskomponenter til slutt i dokumentet.), eller det er irr på kontakten til NO-terminalen på bryteren. Signalet kan da ikke detekteres av kortet. NC-signalet trigger 7-utbetaling av hvis dette detekteres alene.

### Hvis gevinstdisplayet teller ned raskere enn mynter utbetales
Hopper-bryteren er defekt og må byttes. Se forslag til erstatningskomponenter til slutt i dokumentet.

### Hvis hopperen ikke stopper ved gevinstutbetaling.
Hopperen betaler ut en mynt ved hver kvart aktivering av hopperbryterenrotasjon. Hvor langt rotoren har rotert, detekteres av hopper-bryteren. Hvis bryteren er defekt, så vil ikke automaten kunne detektere hvor mange mynter som er utbetalt og dermed tømme hele gevinstrøret.

Kortet er testet med både NC og NO tilkobling. Mulig erstatningsbryter er: DigiKey delenummer: SW872-ND

![hopper1](pictures/hopper_topp.png)

![hopper2](pictures/hopper_underside.png)

### Reservedeler

Orginale reservedeler er omtrent umulig å oppdrive. Under finner du en liste med forslag til mulige erstatningskomponenter, basert på passform og spesifikasjon:

* Brytere til gevinstporter: Crouzet 83137004. DigiKey delenummer: 1463-1000-ND. (Det finnes leverandører som tilbyr nesten identiske brytere på AliExpress til en mye mer overkommelig pris (søk etter "5pcs ZIPPY 5A Micro Switch 3Pin With 10cm 100mm Needle "). Skrufestene på disse passer med akrylblokkene i spillet, men bryteren bygger ca 2 millimeter ekstra. Armen må bøyes til manuelt for at de skal passe i spillet. Pga den ekstra tykkelsen, så går armen også lenger ut enn på de orginale bryterne.)
* Bryter til hopper: Omron SS-5GL2-FT. DigiKey delenummer: SW872-ND
* Transformator: RS delenummer: 504-583 ? (ubekreftet)

