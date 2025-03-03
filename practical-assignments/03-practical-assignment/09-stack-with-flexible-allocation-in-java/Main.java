import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;
import java.util.Locale;
import java.util.Scanner;
import java.io.RandomAccessFile;

/**
 * TP03Q09 - Pilha com Alocação Flexível em Java
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 09/11/2024
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
    
    public Pokemon(int id, int generation, String name, String description, ArrayList<String> types, ArrayList<String> abilities, double weight, double height, int captureRate, boolean isLegendary, Date captureDate) {
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
    
    public Pokemon Clone() {
        return new Pokemon(
            this.id,
            this.generation,
            this.name,
            this.description,
            this.types,
            this.abilities,
            this.weight,
            this.height,
            this.captureRate,
            this.isLegendary,
            this.captureDate
        );
    }
}

class Cell {
    public Pokemon pokemon;
    public Cell next;
    
    public Cell() {
        this(null);
    }
    
    public Cell(Pokemon pokemon) {
        this.pokemon = pokemon;
        this.next = null;
    }
}

class Stack {
    private Cell top;
    private int size;
    
    public Stack() {
        top = null;
    }
    
    public void insert(Pokemon pokemon) {
        Cell temp = new Cell(pokemon);
        temp.next = top;
        top = temp;
        temp = null;
        size++;
    }
    
    public Pokemon remove() throws Exception {
        if (top == null) {
            throw new Exception("Erro ao remover.");
        }

        Pokemon response = top.pokemon;
        Cell temp = top;
        top = top.next;
        temp.next = null;
        temp = null;
        size--;

        return response;
    }
    
    public void show() {
        show(top, 0);
    }
    
    private void show(Cell i, int count) {
        if (i != null) {
            show(i.next, ++count);

            SimpleDateFormat outputDateFormat = new SimpleDateFormat("dd/MM/yyyy");
            String formattedDate = outputDateFormat.format(i.pokemon.getCaptureDate());

            System.out.println("[" + (size - count) + "] [#"
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
                    + formattedDate
            );
        }
    }
}

class ManagePokemon {
    private static Pokemon pokemon[] = new Pokemon[801];
    
    public Pokemon createPokemon(String linha) {
        Pokemon pokemon = new Pokemon();
        SimpleDateFormat ddf = new SimpleDateFormat("dd/MM/yyyy", Locale.ENGLISH);
        String[] fields = linha.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)");

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
                .split(", ")
            )
        );

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
    
    public Pokemon[] readCsv() {
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
        Pokemon responsePokemon = new Pokemon();

        for (int i = 0; i < 801; i++) {
            if (pokemon[i].getId() == id) {
                responsePokemon = pokemon[i];
                break;
            }
        }

        return responsePokemon;
    }
}

public class Main {
    public static int comparisons;
    public static int movements;
    
    public static void saveExecutionFile(String filename, int comparisons, int movements, long endTime) {
        try (RandomAccessFile file = new RandomAccessFile(filename, "rw")) {
            file.writeChars("847235\t" + comparisons + "\t" + movements + "\t" + endTime + "ms");
            file.close();
        } catch (IOException err) {
            System.err.println("Erro ao criar arquivo." + err.getMessage());
        }
    }
    
    public static boolean isEnd(String input) {
        return (input.length() == 3 && input.charAt(0) == 'F' && input.charAt(1) == 'I' && input.charAt(2) == 'M');
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        boolean stop = true;
        int i = 0;
        int k = 0;

        ManagePokemon mp = new ManagePokemon();
        mp.readCsv();

        Stack pokemonsStack = new Stack();
        Pokemon deletedPokemons[] = new Pokemon[20];

        while (stop) {
            String input = sc.nextLine();

            if (isEnd(input)) {
                stop = false;
            } else {
                int id = Integer.parseInt(input);

                try {
                    Pokemon poke = mp.searchPokemon(id);
                    pokemonsStack.insert(poke);
                    i++;
                } catch (Exception e) {
                    System.out.println("Pokemon não encontrado: " + e.getMessage());
                }
            }
        }

        int operationsNumber = sc.nextInt();
        long start = System.currentTimeMillis();

        for (int j = 0; j < operationsNumber; j++) {
            String operation = sc.next();
            comparisons++;

            if (operation.equals("I")) {
                int number = sc.nextInt();

                try {
                    movements++;
                    pokemonsStack.insert(mp.searchPokemon(number));
                } catch (Exception e) {
                    System.out.println("Pokemon não encontrado: " + e.getMessage());
                }
            } else {
                comparisons++;
            }

            if (operation.equals("R")) {
                try {
                    movements++;
                    deletedPokemons[k++] = pokemonsStack.remove();
                } catch (Exception e) {
                    System.out.println("Lista vazia: " + e.getMessage());
                }
            }
        }

        long endTime = System.currentTimeMillis() - start;

        for (int j = 0; j < k; j++) {
            System.out.println("(R) " + deletedPokemons[j].getName());
        }

        pokemonsStack.show();

        sc.close();

        saveExecutionFile("847235_PilhaFlexivel.txt", comparisons, movements, endTime);
    }
}