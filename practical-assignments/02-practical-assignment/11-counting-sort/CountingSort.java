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
 * TP02Q11 - Counting Sort
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 08/10/2024
 */

/**
 * A classe Pokemon representa um Pokémon com diversos atributos como id, geração,
 * nome, descrição, tipos, habilidades, peso, altura, taxa de captura, status de lendário
 * e data de captura.
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

    /**
     * Construtor que inicializa todos os atributos de um Pokémon com os valores fornecidos.
     */
    public Pokemon(int id, int generation, String name, String description, List<String> types, List<String> abilities, double weightKg, double heightM, int captureRate, boolean isLegendary, Date captureDate) {
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

    /**
     * Construtor padrão que inicializa um Pokémon com valores default.
     */
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

    /**
     * Retorna o nome do Pokémon. Necessário para acessar o valor privado
     * e utilizá-lo na pesquisa sequencial por nome.
     *
     * @return o nome do Pokémon
     */
    public String getName() {
        return name;
    }

    /**
     * Retorna a taxa de captura do Pokémon. Necessário para acessar o valor privado
     * e utilizá-lo na ordenação por taxa de captura.
     *
     * @return a taxa de captura do Pokémon
     */
    public int getCaptureRate() {
        return captureRate;
    }

    /**
     * Exibe as informações do Pokémon no console.
     */
    public void displayInformation() {
        System.out.println(this);
    }

    /**
     * Lê os dados de um arquivo CSV e retorna uma lista de Pokémons correspondentes aos IDs procurados.
     *
     * @param searchedIDS uma lista com os IDs dos Pokémons que se deseja procurar
     * @return uma lista de objetos Pokemon
     * @throws IOException caso ocorra um erro ao acessar o arquivo CSV
     * @throws ParseException caso ocorra um erro ao formatar a data
     */
    public static List<Pokemon> read(List<Integer> searchedIDS) throws IOException, ParseException {
        String csvFile = "/tmp/pokemon.csv";
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

                    Pokemon pokemon = new Pokemon(id, generation, name, description, types, abilitiesList, weight, height, captureRate, isLegendary, captureDate);
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

    /**
     * Analisa uma linha do arquivo CSV e retorna um array de Strings contendo os valores separados.
     *
     * @param line uma linha do arquivo CSV
     * @return um array de Strings contendo os valores da linha
     */
    private static String[] parseCsvLine(String line) {
        Pattern pattern = Pattern.compile(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)");
        return pattern.split(line.trim());
    }

    /**
     * Retorna uma representação textual dos atributos do Pokémon.
     *
     * @return uma String formatada com os detalhes do Pokémon
     */
    @Override
    public String toString() {
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy", Locale.ENGLISH);
        String formattedDate = dateFormat.format(captureDate);
        String formattedAbilities = abilities.stream().map(ability -> "'" + ability + "'").collect(Collectors.joining(", "));
        String formattedTypes = types.stream().filter(type -> type != null && !type.isEmpty()).map(type -> "'" + type + "'").collect(Collectors.joining(", "));

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
            formattedDate
        );
    }
}

/**
 * A classe `CountingSort` é responsável por interagir com o usuário, recebendo uma lista de IDs de Pokémons,
 * lendo os dados correspondentes a partir de um arquivo CSV, ordenando os Pokémons pela taxa de captura 
 * utilizando o algoritmo de ordenação por contagem (Counting Sort) e exibindo as informações dos Pokémons
 * ordenados. Além disso, ela contabiliza o número de comparações, movimentos e o tempo de execução da
 * ordenação, registrando esses valores em um arquivo de log.
 */
public class CountingSort {
    public static long[] countingSort(List<Pokemon> array, long startTime) {
        int maxCaptureRate = array.stream().mapToInt(Pokemon::getCaptureRate).max().orElse(0);
        int[] count = new int[maxCaptureRate + 1];

        long comparisons = 0;
        long movements = 0;

        for (Pokemon pokemon : array) {
            count[pokemon.getCaptureRate()]++;
            movements++;
        }

        for (int i = 1; i <= maxCaptureRate; i++) {
            count[i] += count[i - 1];
            comparisons++;
        }

        Pokemon[] output = new Pokemon[array.size()];

        for (int i = array.size() - 1; i >= 0; i--) {
            Pokemon pokemon = array.get(i);
            int captureRate = pokemon.getCaptureRate();
            output[count[captureRate] - 1] = pokemon;
            count[captureRate]--;
            movements++;
        }

        for (int i = 0; i < output.length - 1; i++) {
            for (int j = i + 1; j < output.length; j++) {
                comparisons++;

                if (output[i].getCaptureRate() == output[j].getCaptureRate() && output[i].getName().compareTo(output[j].getName()) > 0) {
                    Pokemon temp = output[i];

                    output[i] = output[j];
                    output[j] = temp;

                    movements++;
                }
            }
        }

        for (int i = 0; i < array.size(); i++) {
            array.set(i, output[i]);
            movements++;
        }

        long endTime = System.currentTimeMillis();
        long duration = endTime - startTime;

        return new long[] { 
            duration, comparisons, movements 
        };
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

            long[] results = countingSort(pokemons, startTime);

            long duration = results[0];
            long comparisons = results[1];
            long movements = results[2];

            for (Pokemon pokemon : pokemons) {
                pokemon.displayInformation();
            }

            try (PrintWriter logWriter = new PrintWriter(new FileWriter("847235_countingsort.txt"))) {
                logWriter.printf("847235\t%d\t%d\t%d\n", comparisons, movements, duration);
            }

        } catch (IOException | ParseException e) {
            e.printStackTrace();
        }
    }
}