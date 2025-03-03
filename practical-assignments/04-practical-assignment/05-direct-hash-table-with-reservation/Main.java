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
 * TP04Q05 - Tabela Hash Direta com Reserva
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 03/12/2024
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
}

class ManagePokemon {
    private static Pokemon pokemon[] = new Pokemon[801];
    
    public Pokemon createPokemon(String line) {
        Pokemon pokemon = new Pokemon();
        SimpleDateFormat ddf = new SimpleDateFormat("dd/MM/yyyy", Locale.ENGLISH);
        String[] fields = line.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)");
     
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
    
    public Pokemon[] readPokemon() {
        int i = 0;
 
        try (BufferedReader br = new BufferedReader(new FileReader("../tmp/pokemon.csv"))) {
            String line = br.readLine();
 
            line = br.readLine();
 
            while (line != null) {
                pokemon[i++] =  createPokemon(line);
                line = br.readLine();
            }
        } catch (IOException e) {
            System.out.println("Erro ao ler o arquivo: " + e.getMessage());
        }
 
        return pokemon;
    }
    
    public Pokemon searchPokemon(int id) {
        Pokemon returnedPokemon = new Pokemon();
        int i = 0;

        for (i = 0; i < 801; i++) {
            if (pokemon[i].getId() == id) {
                returnedPokemon = pokemon[i];
            }
        }

        return returnedPokemon;
    }
    
    public int swap(int i, int j) {
        Pokemon temp = pokemon[i];
        pokemon[i] = pokemon[j];
        pokemon[j] = temp; 
        
        return 3;
    }
}

class GlobalVariables {
    public static int comparisons;
    public static int movements;
    
    public GlobalVariables(){
        comparisons = 0;
        movements = 0;
    }
}

class Hash {
    private Pokemon table[];
    int m1, m2, m, reserve;
    final Pokemon NULL = new Pokemon();
    
    public Hash() {
        this(21, 9);
    }
    
    public Hash(int m1, int m2) {
        this.m1 = m1;
        this.m2 = m2;
        this.m = m1 + m2;
        this.table = new Pokemon[this.m];

        for (int i = 0; i < m; i++) {
            table[i] = NULL;
        }
        
        reserve = 0;
    }
    
    public int h(String name) {
        int sum = 0;
        for (int i = 0; i < name.length(); sum += (int) name.charAt(i), i++);
        return  sum % m1;
    }
    
    public boolean insert(Pokemon pokemon) {
        boolean response = false;

        if (pokemon != NULL) {
            GlobalVariables.comparisons++;
            int position = h(pokemon.getName());

            if (table[position] == NULL) {
                GlobalVariables.comparisons++; 
                table[position] = pokemon;
                response = true;
            } else if (reserve < m2) {
                GlobalVariables.comparisons++; 
                table[m1 + reserve] = pokemon;
                reserve++;
                response = true; 
            }
        }

        return response;
    }
    
    public int search(String name) {
        boolean response = false;
        int position = h(name);
        int responsePosition = 0;

        if (table[position].getName().equals(name)) {
            GlobalVariables.comparisons++;
            response = true;
            responsePosition = position;
        } else if (table[position] != NULL) {
            GlobalVariables.comparisons++;
            for (int i = 0; i < reserve; i++) {
                if (table[m1 + i].getName().equals(name)) {
                    GlobalVariables.comparisons++;
                    response = true;
                    responsePosition = (m1 + i);
                    i = reserve;
                }
            }
        }

        return response ? responsePosition : -1;
    }
}
 
public class Main {
    public static void saveExecutionFile(String filename, int comparisons, int movements, long endTime) {

        try (RandomAccessFile file = new RandomAccessFile(filename, "rw")) {
            file.writeChars("847235\t"+ comparisons + "\t" + movements + "\t" + endTime +"ms");
            file.close();
        } catch(IOException err) {
            System.err.println("Erro no arquivo criado: " + err.getMessage());
        }
    }
    
    public static boolean isEnd(String input) {
        return (input.length() == 3 && input.charAt(0) == 'F' && input.charAt(1) == 'I' && input.charAt(2) == 'M');
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        boolean stop = true;
        
        ManagePokemon mp = new ManagePokemon();

        mp.readPokemon();

        Hash table = new Hash();
        long start = System.currentTimeMillis();
                
        while (stop) {
            String input = sc.nextLine();
            
            if (isEnd(input)) {
                stop = false;
            } else {
                int id = Integer.parseInt(input);

                try {
                    Pokemon pokemon = mp.searchPokemon(id);
                    table.insert(pokemon);
                } catch(Exception e) {
                    System.out.println("Pokemon não encontrado: " + e.getMessage());
                }
            }
        }

        stop = true;
        
        while (stop) {
            String input = sc.nextLine();
            
            if (isEnd(input)) {
                stop = false;
            } else {
                int response = table.search(input);
                System.out.println("=> " + input + ": " + (response != -1 ? "(Posicao: "+ response +") SIM" : "NAO"));
            }
        }
           
        long endTime = System.currentTimeMillis() - start;

        sc.close();

        saveExecutionFile("847235_hashReserva.txt", GlobalVariables.comparisons, GlobalVariables.movements, endTime);
    }
}