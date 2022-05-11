package hr.fer.oop.utr.lab1;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class EpsilonNFA {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String ulazniWOS = br.readLine();
        String[] ulazniNizovi = ulazniWOS.split("\\|");

        Map<String, Map<String, List<String>>> prijelazi = new TreeMap<>();

        String pocetnoStanje = br.readLine();

        String funkcijaPrijelaza;
        while((funkcijaPrijelaza = br.readLine()) != null && funkcijaPrijelaza.length() > 0) {
            int count = funkcijaPrijelaza.length() -
                    funkcijaPrijelaza.replace(",", "").length();
            String s[] = funkcijaPrijelaza.split(",", count + 1);

            String pom[] = s[1].split("->");

            List<String> lista = new ArrayList<>();
            lista.add(pom[1]);
            for(int i = 2; i <= count; i++)
                lista.add(s[i]);
            Collections.sort(lista);
            if (prijelazi.containsKey(s[0])) {
                Map<String, List<String>> stringListMap = prijelazi.get(s[0]);
                stringListMap.put(pom[0], lista);
                prijelazi.put(s[0], stringListMap);
            } else {
                Map<String, List<String>> stringListMap = new HashMap<>();
                stringListMap.put(pom[0], lista);
                prijelazi.put(s[0], stringListMap);
            }
        }
        br.close();

        String[] pocetna = new String[1];
        pocetna[0] = pocetnoStanje;

        for (int i = 0; i < ulazniNizovi.length; i++) {
            printThemMFs(pocetna, ulazniNizovi[i], prijelazi);
            if (i < ulazniNizovi.length - 1)
                System.out.println();
        }
    }

    public static void printThemMFs(String[] trenutnaStanja, String ulazniNiz,
                                    Map<String, Map<String, List<String>>> prijelazi) {


        //u listu skup dodaj stanja u kojima se trenutno nalazimo
        List<String> skupTrenutnih = new ArrayList<>();
        for (int i = 0; i < trenutnaStanja.length; i++)
            skupTrenutnih.add(trenutnaStanja[i]);

        //dodaj jos epsilon okolinu trenutnih stanja
        List<String> epsilonStanja = new ArrayList<>();
        for (String stanje: trenutnaStanja)
            nadjiEpsilonOkolinu(stanje, epsilonStanja, prijelazi);
        for (String s : epsilonStanja) {
            skupTrenutnih.add(s);
        }

        //ukloni duplikate iz liste i leksikografski poslozi
        Set<String> set = new LinkedHashSet<>();
        set.addAll(skupTrenutnih);
        skupTrenutnih.clear();
        skupTrenutnih.addAll(set);
        Collections.sort(skupTrenutnih);

        if (skupTrenutnih.contains("#") ) {
            skupTrenutnih.remove("#");
            if (skupTrenutnih.isEmpty())
                skupTrenutnih.add("#");
        }


        for (int i = 0; i < skupTrenutnih.size(); i++) {
            if (i < skupTrenutnih.size() - 1)
                System.out.print(skupTrenutnih.get(i) + ",");
            else
                System.out.print(skupTrenutnih.get(i));
        }

        List<String> sljedecaStanja = new ArrayList<>();

        //ako postoji vise znakova u ulaznom nizu
        if (ulazniNiz.contains(",")) {
            String[] ulazniZnakovi = ulazniNiz.split(",", 2);
            //pronalazenje prijelaza sa ulaznim znakom
            for(String stanje: skupTrenutnih) {
                //za svako trenutno stanje naci prijelaz sa prvim ulaznim znakom
                if (prijelazi.containsKey(stanje) && prijelazi.get(stanje).containsKey(ulazniZnakovi[0])) {
                    for (String novoStanje : prijelazi.get(stanje).get(ulazniZnakovi[0])) {
                        sljedecaStanja.add(novoStanje);
                    }
                }
            }
            // pronasli smo sva sljedeca stanja
        } else {
            //slucaj kad je samo jedan znak u ulaznom nizu
            for(String stanje: skupTrenutnih) {
                //za svako trenutno stanje naci prijelaz sa prvim ulaznim znakom
                if (prijelazi.containsKey(stanje) && prijelazi.get(stanje).containsKey(ulazniNiz)) {
                    for (String novoStanje : prijelazi.get(stanje).get(ulazniNiz)) {
                        if (!novoStanje.equals("#")) {
                            sljedecaStanja.add(novoStanje);
                        }
                    }
                }
            }
            Collections.sort(sljedecaStanja);

            if (sljedecaStanja.size() == 0) {
                System.out.printf("|#");
            } else {
                //nadji i epsilon okolinu sljedecih stanja jer nema vise prijelaza
                System.out.printf("|");
                List<String> epsiloni = new ArrayList<>();
                for (String st: sljedecaStanja)
                    nadjiEpsilonOkolinu(st, epsiloni, prijelazi);
                for(String s: epsiloni) {
                    sljedecaStanja.add(s);
                }
                Set<String> setSljedecih = new LinkedHashSet<>();
                setSljedecih.addAll(sljedecaStanja);
                sljedecaStanja.clear();
                sljedecaStanja.addAll(setSljedecih);
                Collections.sort(sljedecaStanja);
                for (int i = 0; i < sljedecaStanja.size(); i++) {
                    if (i < sljedecaStanja.size() - 1)
                        System.out.print(sljedecaStanja.get(i) + ",");
                    else
                        System.out.print(sljedecaStanja.get(i));
                }
            }
            return;
        }
        System.out.printf("|");

        //ako nema nijedno sljedece stanje, treba ispisivat #
        if (sljedecaStanja.size() == 0) {
            int cnt = ulazniNiz.length() -
                    ulazniNiz.replace(",", "")
                            .length() + 1;
            for (int i = 0; i < cnt; i++) {
                if (i < cnt - 1)
                    System.out.printf("#|");
                else
                    System.out.printf("#");
            }
            return;
        }

        String[] ulazniZnakovi = ulazniNiz.split(",", 2);
        printThemMFs(sljedecaStanja.toArray(
                        new String[sljedecaStanja.size()]),
                ulazniZnakovi[1], prijelazi);
    }

    public static void nadjiEpsilonOkolinu(String stanje, List<String> epsilonOkolina,
                                           Map<String, Map<String, List<String>>> prijelazi) {

        epsilonOkolina.add(stanje);
        if (prijelazi.containsKey(stanje) && prijelazi.get(stanje).containsKey("$")) {
            for (String s : prijelazi.get(stanje).get("$")) {
                if (!epsilonOkolina.contains(s) && !(s.equals("#"))) {
                    nadjiEpsilonOkolinu(s, epsilonOkolina, prijelazi);
                }
            }
        }
    }
}