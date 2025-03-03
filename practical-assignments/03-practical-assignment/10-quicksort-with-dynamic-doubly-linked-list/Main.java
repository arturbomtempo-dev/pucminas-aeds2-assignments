import java.text.SimpleDateFormat;
import java.text.ParseException;
import java.io.RandomAccessFile;
import java.io.BufferedReader;
import java.io.IOException;
import java.util.ArrayList;
import java.io.FileReader;
import java.util.Scanner;
import java.util.Arrays;
import java.util.Locale;
import java.util.Date;

/**
 * TP03Q10 - Quicksort com LISTA DINÂMICA DUPLAMENTE ENCADEADA em Java
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 15/11/2024
 */

class Pokemon {
    private int id;
    private int generation;
    private String name;
    private String description;
    private ArrayList<String> types;
    private ArrayList<String> abilities;
    private double weight;
    private double height;
    private int captureRate;
    private boolean isLegendary;
    private Date captureDate;

    public Pokemon() {
        this.id = 0;
        this.generation = 0;
        this.name = "";
        this.description = "";
        this.types = new ArrayList<String>();
        this.abilities = new ArrayList<String>();
        this.weight = 0.0;
        this.height = 0.0;
        this.captureRate = 0;
        this.isLegendary = false;
        this.captureDate = new Date();
    }

    public Pokemon(int id, int generation, String name, String description, ArrayList<String> types,
            ArrayList<String> abilities, double weight, double height, int captureRate, boolean isLegendary,
            Date captureDate) {
        this.id = id;
        this.generation = generation;
        this.name = name;
        this.description = description;
        this.types = types;
        this.abilities = abilities;
        this.weight = weight;
        this.height = height;
        this.captureRate = captureRate;
        this.isLegendary = isLegendary;
        this.captureDate = captureDate;
    }

    public int getId() {
        return this.id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getGeneration() {
        return this.generation;
    }

    public void setGeneration(int generation) {
        this.generation = generation;
    }

    public String getName() {
        return this.name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getDescription() {
        return this.description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public ArrayList<String> getTypes() {
        return this.types;
    }

    public void setTypes(ArrayList<String> types) {
        this.types = types;
    }

    public ArrayList<String> getAbilities() {
        return this.abilities;
    }

    public void setAbilities(ArrayList<String> abilities) {
        this.abilities = abilities;
    }

    public double getWeight() {
        return this.weight;
    }

    public void setWeight(double weight) {
        this.weight = weight;
    }

    public double getHeight() {
        return this.height;
    }

    public void setHeight(double height) {
        this.height = height;
    }

    public int getCaptureRate() {
        return this.captureRate;
    }

    public void setCaptureRate(int captureRate) {
        this.captureRate = captureRate;
    }

    public boolean getIsLegendary() {
        return this.isLegendary;
    }

    public void setIsLegendary(boolean isLegendary) {
        this.isLegendary = isLegendary;
    }

    public Date getCaptureDate() {
        return this.captureDate;
    }

    public void setCaptureDate(Date captureDate) {
        this.captureDate = captureDate;
    }
}

class GlobalVariables {
    public static int comparisons;
    public static int movements;

    public GlobalVariables() {
        comparisons = 0;
        movements = 0;
    }

    public static int getComparisons() {
        return comparisons;
    }

    public static int getMovements() {
        return movements;
    }
}

class DoubleCell {
    public Pokemon pokemon;
    public DoubleCell next, previous;

    public DoubleCell() {
        this(null);
    }

    public DoubleCell(Pokemon pokemon) {
        this.pokemon = pokemon;
        this.next = null;
    }
}

class DoubleList {
    private DoubleCell first, last;
    private int size;

    public DoubleList() {
        first = new DoubleCell();
        last = first;
    }

    public DoubleCell getFirst() {
        return this.first;
    }

    public DoubleCell getLast() {
        return this.last;
    }

    public int getSize() {
        return size;
    }

    public void insertEnd(Pokemon pokemon) {
        last.next = new DoubleCell(pokemon);
        last.next.previous = last;
        last = last.next;
        size++;
    }

    public Pokemon removeStart() throws Exception {
        if (first == last) {
            throw new Exception("Erro ao remover elemento no início da lista.");
        }

        DoubleCell temp = first;
        first = first.next;
        Pokemon response = first.pokemon;
        temp.next = first.previous = null;
        temp = null;
        size--;

        return response;
    }

    public Pokemon removeEnd() throws Exception {
        if (first == last) {
            throw new Exception("Erro ao remover elemento da lista.");
        }

        Pokemon response = last.pokemon;
        last = last.previous;
        last.next.previous = null;
        last.next = null;
        size--;

        return response;
    }

    public void show() {
        show(first.next, 0);
    }

    private void show(DoubleCell i, int count) {
        if (i != null) {
            SimpleDateFormat outputDateFormat = new SimpleDateFormat("dd/MM/yyyy");
            String formattedDate = outputDateFormat.format(i.pokemon.getCaptureDate());

            System.out.println("[#"
                    + i.pokemon.getId() + " -> "
                    + i.pokemon.getName() + ": "
                    + i.pokemon.getDescription() + " - "
                    + i.pokemon.getTypes() + " - "
                    + i.pokemon.getAbilities() + " - "
                    + i.pokemon.getWeight() + "kg - "
                    + i.pokemon.getHeight() + "m - "
                    + i.pokemon.getCaptureRate() + "% - "
                    + i.pokemon.getIsLegendary() + " - "
                    + i.pokemon.getGeneration() + " gen] - "
                    + formattedDate);

            show(i.next, ++count);
        }
    }

    private DoubleCell getPivot(int position, DoubleList list) {
        DoubleCell current = list.first.next;

        for (int i = 0; i < position && current != null; i++) {
            current = current.next;
        }

        return current;
    }

    public void swap(DoubleCell ci, DoubleCell cj) {
        Pokemon temp = ci.pokemon;
        ci.pokemon = cj.pokemon;
        cj.pokemon = temp;
    }

    public void quicksort(DoubleList list, int left, int right, DoubleCell cLeft, DoubleCell cRight) {
        DoubleCell ci = cLeft, cj = cRight;
        DoubleCell pivot = getPivot(left, list);
        int i = left, j = right;

        while (i <= j) {
            while (ci.pokemon.getGeneration() < pivot.pokemon.getGeneration()
                    || (ci.pokemon.getGeneration() == pivot.pokemon.getGeneration()
                            && ci.pokemon.getName().compareTo(pivot.pokemon.getName()) < 0)) {
                GlobalVariables.comparisons++;
                i++;
                ci = ci.next;
            }

            while (cj.pokemon.getGeneration() > pivot.pokemon.getGeneration()
                    || (cj.pokemon.getGeneration() == pivot.pokemon.getGeneration()
                            && cj.pokemon.getName().compareTo(pivot.pokemon.getName()) > 0)) {
                GlobalVariables.comparisons++;
                j--;
                cj = cj.previous;
            }

            if (i <= j) {
                GlobalVariables.movements += 3;
                swap(ci, cj);
                ci = ci.next;
                cj = cj.previous;
                i++;
                j--;
            }
        }

        if (left < j) {
            quicksort(list, left, j, cLeft, cj);
        }

        if (i < right) {
            quicksort(list, i, right, ci, cRight);
        }
    }
}

class ManagePokemon {
    private static Pokemon pokemon[] = new Pokemon[801];

    public Pokemon createPokemon(String row) {
        Pokemon pokemon = new Pokemon();
        SimpleDateFormat ddf = new SimpleDateFormat("dd/MM/yyyy", Locale.ENGLISH);
        String[] fields = row.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)");

        pokemon.setId(Integer.parseInt(fields[0]));
        pokemon.setGeneration(Integer.parseInt(fields[1]));
        pokemon.setName(fields[2]);
        pokemon.setDescription(fields[3]);

        ArrayList<String> types = new ArrayList<>();

        types.add("'" + fields[4] + "'");

        if (!fields[5].isEmpty()) {
            types.add("'" + fields[5] + "'");
        }

        pokemon.setTypes(types);

        pokemon.getAbilities().addAll(
                Arrays.asList(
                        fields[6]
                                .replace("\"", "")
                                .replace("[", "")
                                .replace("]", "")
                                .split(", ")));

        pokemon.setWeight(fields[7].isEmpty() ? 0.0 : Double.parseDouble(fields[7]));
        pokemon.setHeight(fields[8].isEmpty() ? 0.0 : Double.parseDouble(fields[8]));
        pokemon.setCaptureRate(Integer.parseInt(fields[9]));
        pokemon.setIsLegendary(fields[10].equals("1"));

        try {
            pokemon.setCaptureDate(ddf.parse(fields[11]));
        } catch (ParseException e) {
            e.printStackTrace();
        }

        return pokemon;
    }

    public Pokemon[] readPokemon() {
        int i = 0;

        try (BufferedReader br = new BufferedReader(new FileReader("../tmp/pokemon.csv"))) {
            String line = br.readLine();

            line = br.readLine();

            while (line != null) {
                pokemon[i++] = createPokemon(line);
                line = br.readLine();
            }
        } catch (IOException e) {
            System.out.println("Erro ao ler o arquivo: " + e.getMessage());
        }

        return pokemon;
    }

    public Pokemon searchPokemon(int id) {
        int i = 0;

        Pokemon returnedPokemon = new Pokemon();

        for (i = 0; i < 801; i++) {
            if (pokemon[i].getId() == id) {
                returnedPokemon = pokemon[i];
            }
        }

        return returnedPokemon;
    }
}

public class Main {
    public static void saveExecutionFile(String filename, int comparisons, int movements, long endTime) {
        try (RandomAccessFile file = new RandomAccessFile(filename, "rw")) {
            file.writeChars("847235\t" + comparisons + "\t" + movements + "\t" + endTime + "ms");
            file.close();
        } catch (IOException err) {
            System.err.println("Erro no arquivo criado: " + err.getMessage());
        }
    }

    public static boolean isEnd(String input) {
        return (input.length() == 3 && input.charAt(0) == 'F' && input.charAt(1) == 'I' && input.charAt(2) == 'M');
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        boolean stop = true;
        int i = 0;

        ManagePokemon mp = new ManagePokemon();

        mp.readPokemon();

        DoubleList pokemonsList = new DoubleList();

        while (stop) {
            String input = sc.nextLine();

            if (isEnd(input)) {
                stop = false;
            } else {
                try {
                    int id = Integer.parseInt(input.trim());
                    Pokemon pokemon = mp.searchPokemon(id);
                    pokemonsList.insertEnd(pokemon);
                    i++;
                } catch (NumberFormatException e) {
                    System.out.println("Entrada inválida. Por favor, insira um número inteiro.");
                } catch (Exception e) {
                    System.out.println("Pokemon não encontrado: " + e.getMessage());
                }
            }
        }

        long start = System.currentTimeMillis();

        pokemonsList.quicksort(pokemonsList, 0, pokemonsList.getSize() - 1, pokemonsList.getFirst().next,
                pokemonsList.getLast());

        long endTime = System.currentTimeMillis() - start;

        pokemonsList.show();

        sc.close();

        saveExecutionFile("847235_quicksort3.txt", GlobalVariables.getComparisons(), GlobalVariables.getMovements(),
                endTime);
    }
}