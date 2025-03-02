import java.util.stream.Collectors;
import java.text.SimpleDateFormat;
import java.text.ParseException;
import java.util.regex.Pattern;
import java.io.BufferedReader;
import java.util.ArrayList;
import java.io.IOException;
import java.io.FileReader;
import java.util.HashMap;
import java.util.Scanner;
import java.util.Locale;
import java.util.Arrays;
import java.util.Date;
import java.util.List;
import java.io.FileWriter;
import java.io.PrintWriter;

/**
 * TP02Q09 - Heapsort
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 08/10/2024
 */

class Pokemon {
    private int id;
    private int generation;
    private String name;
    private String description;
    private List<String> types;
    private List<String> abilities;
    private double weightKg;
    private double heightM;
    private int captureRate;
    private boolean isLegendary;
    private Date captureDate;

    public Pokemon(int id, int generation, String name, String description, List<String> types, List<String> abilities,
            double weightKg, double heightM, int captureRate, boolean isLegendary, Date captureDate) {
        this.id = id;
        this.generation = generation;
        this.name = name;
        this.description = description;
        this.types = types;
        this.abilities = abilities;
        this.weightKg = weightKg;
        this.heightM = heightM;
        this.captureRate = captureRate;
        this.isLegendary = isLegendary;
        this.captureDate = captureDate;
    }

    public Pokemon() {
        this.id = -1;
        this.generation = -1;
        this.name = "Unknown";
        this.description = "No description";
        this.types = new ArrayList<>(Arrays.asList("Normal"));
        this.abilities = new ArrayList<>(Arrays.asList("None"));
        this.weightKg = 1.0;
        this.heightM = 1.0;
        this.captureRate = 100;
        this.isLegendary = false;
        this.captureDate = new Date();
    }

    public String getName() {
        return name;
    }

    public double getHeightM() {
        return heightM;
    }

    public void displayInformation() {
        System.out.println(this);
    }

    public static List<Pokemon> read(List<Integer> searchedIDS) throws IOException, ParseException {
        String csvFile = "../tmp/pokemon.csv";
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy", Locale.ENGLISH);
        List<Pokemon> pokemons = new ArrayList<>();
        HashMap<Integer, Pokemon> listPokemon = new HashMap<>();

        try (BufferedReader reader = new BufferedReader(new FileReader(csvFile))) {
            String line;
            reader.readLine();

            while ((line = reader.readLine()) != null) {
                String[] values = parseCsvLine(line);
                int id = Integer.parseInt(values[0]);

                if (searchedIDS.contains(id)) {
                    int generation = Integer.parseInt(values[1]);
                    String name = values[2];
                    String description = values[3];
                    List<String> types = new ArrayList<>();

                    types.add(values[4].isEmpty() ? null : values[4]);

                    if (!values[5].isEmpty()) {
                        types.add(values[5]);
                    }

                    String abilitiesString = values[6];
                    String cleanAbilities = abilitiesString.replaceAll("[\\[\\]\"']", "");
                    List<String> abilitiesList = Arrays.asList(cleanAbilities.split(",\\s*"));
                    double weight = values[7].isEmpty() ? 0 : Double.parseDouble(values[7]);
                    double height = values[8].isEmpty() ? 0 : Double.parseDouble(values[8]);
                    int captureRate = values[9].isEmpty() ? 0 : Integer.parseInt(values[9]);
                    boolean isLegendary = Integer.parseInt(values[10]) == 1;
                    Date captureDate = dateFormat.parse(values[11]);

                    Pokemon pokemon = new Pokemon(id, generation, name, description, types, abilitiesList, weight,
                            height, captureRate, isLegendary, captureDate);

                    listPokemon.put(id, pokemon);
                }
            }
        }

        for (Integer id : searchedIDS) {
            if (listPokemon.containsKey(id)) {
                pokemons.add(listPokemon.get(id));
            }
        }

        return pokemons;
    }

    private static String[] parseCsvLine(String line) {
        Pattern pattern = Pattern.compile(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)");
        return pattern.split(line.trim());
    }

    @Override
    public String toString() {
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy", Locale.ENGLISH);
        String formattedDate = dateFormat.format(captureDate);
        String formattedAbilities = abilities.stream().map(ability -> "'" + ability + "'")
                .collect(Collectors.joining(", "));
        String formattedTypes = types.stream().filter(type -> type != null && !type.isEmpty())
                .map(type -> "'" + type + "'").collect(Collectors.joining(", "));

        return String.format(
                "[#%d -> %s: %s - [%s] - [%s] - %.1fkg - %.1fm - %d%% - %b - %d gen] - %s",
                id,
                name,
                description,
                formattedTypes,
                formattedAbilities,
                weightKg,
                heightM,
                captureRate,
                isLegendary,
                generation,
                formattedDate);
    }
}

public class Main {
    public static void heapSort(List<Pokemon> array, long[] counters) {
        int n = array.size();

        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(array, n, i, counters);
        }

        for (int i = n - 1; i > 0; i--) {
            Pokemon temp = array.get(0);
            array.set(0, array.get(i));
            array.set(i, temp);

            counters[1]++;

            heapify(array, i, 0, counters);
        }
    }

    public static void heapify(List<Pokemon> array, int n, int i, long[] counters) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && comparePokemons(array.get(left), array.get(largest), counters) > 0) {
            largest = left;
        }

        if (right < n && comparePokemons(array.get(right), array.get(largest), counters) > 0) {
            largest = right;
        }

        if (largest != i) {
            Pokemon swap = array.get(i);
            array.set(i, array.get(largest));
            array.set(largest, swap);

            counters[1]++;

            heapify(array, n, largest, counters);
        }
    }

    public static int comparePokemons(Pokemon a, Pokemon b, long[] counters) {
        counters[0]++;
        int comparison = Double.compare(a.getHeightM(), b.getHeightM());

        if (comparison == 0) {
            return a.getName().compareTo(b.getName());
        }

        return comparison;
    }

    public static void main(String[] args) {
        List<Integer> searchedIDS = new ArrayList<>();
        long[] counters = { 0, 0 };
        long startTime = System.currentTimeMillis();

        try (Scanner sc = new Scanner(System.in)) {
            String input = sc.nextLine();

            while (!input.equals("FIM")) {
                int id = Integer.parseInt(input);
                searchedIDS.add(id);
                input = sc.nextLine();
            }

            List<Pokemon> pokemons = Pokemon.read(searchedIDS);

            heapSort(pokemons, counters);

            long endTime = System.currentTimeMillis();
            long duration = endTime - startTime;

            for (Pokemon pokemon : pokemons) {
                pokemon.displayInformation();
            }

            try (PrintWriter logWriter = new PrintWriter(new FileWriter("847235_heapsort.txt"))) {
                logWriter.printf("847235\t%d\t%d\t%d\n", counters[0], counters[1], duration);
            }

        } catch (IOException | ParseException e) {
            e.printStackTrace();
        }
    }
}