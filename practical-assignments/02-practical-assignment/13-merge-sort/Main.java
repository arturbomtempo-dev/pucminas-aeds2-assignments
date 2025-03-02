import java.util.stream.Collectors;
import java.text.SimpleDateFormat;
import java.text.ParseException;
import java.util.regex.Pattern;
import java.io.BufferedReader;
import java.util.ArrayList;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.HashMap;
import java.util.Scanner;
import java.util.Locale;
import java.util.Arrays;
import java.util.Date;
import java.util.List;

/**
 * TP02Q13 - Mergesort
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

    public List<String> getTypes() {
        return types;
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
    private static long comparisons = 0;
    private static long movements = 0;

    private static int compareByTypes(Pokemon left, Pokemon right) {
        List<String> leftTypes = left.getTypes();
        List<String> rightTypes = right.getTypes();

        String leftType = leftTypes.isEmpty() ? null : leftTypes.get(0);
        String rightType = rightTypes.isEmpty() ? null : rightTypes.get(0);

        if (leftType != null && rightType != null) {
            int typeComparison = leftType.compareTo(rightType);

            if (typeComparison != 0) {
                return typeComparison;
            }
        }

        return left.getName().compareTo(right.getName());
    }

    public static List<Pokemon> mergeSort(List<Pokemon> array) {
        if (array.size() <= 1) {
            return array;
        }

        int mid = array.size() / 2;
        List<Pokemon> left = mergeSort(array.subList(0, mid));
        List<Pokemon> right = mergeSort(array.subList(mid, array.size()));

        return merge(left, right);
    }

    public static List<Pokemon> merge(List<Pokemon> left, List<Pokemon> right) {
        List<Pokemon> merged = new ArrayList<>();
        int i = 0, j = 0;

        while (i < left.size() && j < right.size()) {
            comparisons++;

            Pokemon leftPokemon = left.get(i);
            Pokemon rightPokemon = right.get(j);
            int typeComparison = compareByTypes(leftPokemon, rightPokemon);

            if (typeComparison < 0) {
                merged.add(leftPokemon);
                i++;
                movements++;
            } else {
                merged.add(rightPokemon);
                j++;
                movements++;
            }
        }

        while (i < left.size()) {
            merged.add(left.get(i));
            i++;
            movements++;
        }

        while (j < right.size()) {
            merged.add(right.get(j));
            j++;
            movements++;
        }

        return merged;
    }

    public static void main(String[] args) {
        List<Integer> searchedIDS = new ArrayList<>();
        long startTime = System.currentTimeMillis();

        try (Scanner sc = new Scanner(System.in)) {
            String input = sc.nextLine();

            while (!input.equals("FIM")) {
                int id = Integer.parseInt(input);

                searchedIDS.add(id);
                input = sc.nextLine();
            }

            List<Pokemon> pokemons = Pokemon.read(searchedIDS);
            pokemons = mergeSort(pokemons);

            long endTime = System.currentTimeMillis();
            long duration = endTime - startTime;

            for (Pokemon pokemon : pokemons) {
                pokemon.displayInformation();
            }

            try (PrintWriter logWriter = new PrintWriter(new FileWriter("847235_mergesort.txt"))) {
                logWriter.printf("847235\t%d\t%d\t%d\n", comparisons, movements, duration);
            }

        } catch (IOException | ParseException e) {
            e.printStackTrace();
        }
    }
}