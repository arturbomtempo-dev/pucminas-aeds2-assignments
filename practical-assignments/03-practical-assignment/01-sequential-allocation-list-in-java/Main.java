import java.util.*;
import java.io.*;
import java.time.*;
import java.time.format.DateTimeFormatter;

/**
 * TP03Q01 - Lista com Alocação Sequencial em Java
 * 
 * @author Artur Bomtempo Colen
 * @version 1.0, 28/10/2024
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
    private LocalDate captureDate;

    public Pokemon() {
        this.id = -1;
        this.generation = -1;
        this.name = "Unknown";
        this.description = "No description";
        this.types = new ArrayList<>(Arrays.asList("Normal"));
        this.abilities = new ArrayList<>(Arrays.asList("None"));
        this.weight = 1.0;
        this.height = 1.0;
        this.captureRate = 100;
        this.isLegendary = false;
        this.captureDate = LocalDate.now();
    }

    public int getId () {
        return id;
    }

    public void setId (int id) {
        this.id = id;
    }


    public int getGeneration () {
        return generation;
    }

    public void setGeneration (int generation) {
        this.generation = generation;
    }


    public String getName () {
        return name;
    }

    public void setName (String name) {
        this.name = name;
    }


    public String getDescription () {
        return description;
    }

    public void setDescription (String description) {
        this.description = description;
    }


    public ArrayList<String> getTypes () {
        return types;
    }

    public void setTypes (ArrayList<String> types) {
        this.types = types;
    }


    public ArrayList<String> getAbilities () {
        return abilities;
    }

    public void setAbilities (ArrayList<String> abilities) {
        this.abilities = abilities;
    }

    public double getWeight () {
        return weight;
    }

    public void setWeight (double weight) {
        this.weight = weight;
    }

    public double getHeight () {
        return height;
    }

    public void setHeight (double height) {
        this.height = height;
    }

    public int getCaptureRate () {
        return captureRate;
    }

    public void setCaptureRate (int captureRate) {
        this.captureRate = captureRate;
    }

    public boolean getIsLegendary () {
        return isLegendary;
    }
    
    public void setIsLegendary (boolean isLegendary) {
        this.isLegendary = isLegendary;
    }
    
    public LocalDate getCaptureDate() {
        return captureDate;
    }

    public void setCaptureDate(LocalDate captureDate) {
        this.captureDate = captureDate;
    }

    public Pokemon (int id, int generation, String name, String description, ArrayList<String> types, ArrayList<String> abilities, double weight, double heigth, int captureRate, boolean isLegendary, LocalDate captureDate) {
        setId(id);
        setGeneration(generation);
        setName(name);
        setDescription(description);
        setTypes(types);
        setAbilities(abilities);
        setWeight(weight);
        setHeight(height);
        setCaptureRate(captureRate);
        setIsLegendary(isLegendary);
        setCaptureDate(captureDate);
    }

    public Pokemon (String line) {
        String[] item = line.split(",");

        setId(Integer.parseInt(item[0]));
        setGeneration(Integer.parseInt(item[1]));
        setName(item[2]);
        setDescription(item[3]);

        ArrayList<String> types = new ArrayList<>();

        types.add(item[4]);

        if (!item[5].isEmpty()) {
            types.add(item[5]);
        }

        setTypes(types);

        int counter = 6;
        boolean IsDouble = false;
        ArrayList<String> abilities = new ArrayList<>();

        while (!IsDouble) {
            try {
                Double.parseDouble(item[counter]); 
                IsDouble = true;
            } catch (NumberFormatException e) {
                if (!item[counter].isEmpty()) {
                    String ability = item[counter].replaceAll("[\\[\\]'\"']", "").trim();

                    abilities.add(ability);
                    counter++;
                } else {
                    IsDouble = true;
                }
            }
        }

        setAbilities(abilities);

        if (!item[counter].isEmpty()) {
            setWeight(Double.parseDouble(item[counter]));
        }

        counter++;

        if (!item[counter].isEmpty()) {
            setHeight(Double.parseDouble(item[counter]));
        }

        counter++;

        setCaptureRate(Integer.parseInt(item[counter]));

        counter++;

        setIsLegendary(item[counter].equals("1"));

        counter++;

        DateTimeFormatter formattedDate = DateTimeFormatter.ofPattern("dd/MM/yyyy");

        setCaptureDate(LocalDate.parse(item[counter], formattedDate));
    }

    public Pokemon clone() {
        Pokemon clone = new Pokemon(getId(), getGeneration(), getName(), getDescription(), getTypes(), getAbilities(), getWeight(), getHeight(), getCaptureRate(), getIsLegendary(), getCaptureDate());
        
        return clone;
    }
 
    public void displayInformation() {
        System.out.printf("[#" + id + " -> " + name + ": " + description + " - [");

        int counter = 1;

        for (String type : types) {
            if (counter == 1) {
                System.out.printf("'" + type + "'");
                counter++;
            } else {
                System.out.printf(", '" + type + "'");
            }
        }

        System.out.printf("] - [");

        counter = 1;

        for (String ability : abilities) {
            if (counter == 1) {
                System.out.printf("'" + ability + "'");
                counter++;
            } else {
                System.out.printf(", '" + ability + "'");
            }
        }

        DateTimeFormatter formattedDate = DateTimeFormatter.ofPattern("dd/MM/yyyy");

        System.out.printf("] - " + weight + "kg - " + height + "m - " + captureRate + "%% - " + isLegendary + " - " + generation + " gen] - " + captureDate.format(formattedDate));

        System.out.println();
    }
}

class List {
    private Pokemon[] array;
    private int n;

    public List(int size) {
        array = new Pokemon[size];
        n = 0;
    }
 
    public List() {
       this(100);
    }
 
    public void insertStart(Pokemon x) throws Exception {
        if (n >= array.length) {
            throw new Exception("Erro ao inserir.");
        }
 
        for (int i = n; i > 0; i--) {
            array[i] = array[i - 1];
        }
 
        array[0] = x;
        n++;
    }
 
    public void insertEnd(Pokemon x) throws Exception {
        if (n >= array.length) {
            throw new Exception("Erro ao inserir.");
        }
 
        array[n] = x;
        n++;
    }
 
    public void insert(Pokemon x, int position) throws Exception {
        if (n >= array.length || position < 0 || position > n) {
            throw new Exception("Erro ao inserir!");
        }
 
        for (int i = n; i > position; i--) {
            array[i] = array[i - 1];
        }
 
        array[position] = x;
        n++;
    }
 
    public Pokemon removeStart() throws Exception {
        if (n == 0) {
            throw new Exception("Erro ao remover.");
        }
 
        Pokemon resp = array[0];

        n--;
 
        for (int i = 0; i < n; i++) {
            array[i] = array[i + 1];
        }
 
        return resp;
    }
 
    public Pokemon removeEnd() throws Exception {
        if (n == 0) {
            throw new Exception("Erro ao remover.");
        }
 
        return array[--n];
    }
 
    public Pokemon remove(int position) throws Exception {
        if (n == 0 || position < 0 || position >= n) {
            throw new Exception("Erro ao remover.");
        }
 
        Pokemon resp = array[position];
        n--;
 
        for (int i = position; i < n; i++) {
            array[i] = array[i + 1];
        }
 
        return resp;
    }
 
    public void show() {
        for (int i = 0; i < n; i++) {
            System.out.print("[" + i + "] ");
            array[i].displayInformation();
        }
    }
 
    public boolean search(Pokemon x) {
       boolean found = false;
       
        for (int i = 0; i < n && found == false; i++) {
            found = (array[i] == x);
        }

        return found;
    }
}

public class Main {
    public static void main(String[] args) {
        ArrayList<Pokemon> pokemons = new ArrayList<Pokemon>();

        try {
            Scanner sc = new Scanner(new File("../tmp/pokemon.csv"));
            sc.nextLine();

            while (sc.hasNextLine()) {
                pokemons.add(new Pokemon(sc.nextLine()));
            }

            sc.close();
        } catch (Exception e) {
            System.out.println("Error.");
        }

        Scanner sc = new Scanner(System.in);

        List pkmns = new List();
        String input = sc.nextLine();

        while (!input.equals("FIM")) {
            int number = Integer.parseInt(input);

            try {
                pkmns.insertEnd(pokemons.get(number - 1));
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }

            input = sc.nextLine();
        }

        int N = sc.nextInt();
        sc.nextLine();

        for (int i = 0; i < N; i++) {
            String line = sc.nextLine();
            String[] array = line.split(" ");
            String type = array[0];
            int number = 0, position = 0;

            if (array.length == 3) {
                position = Integer.parseInt(array[1]);
                number = Integer.parseInt(array[2]);
            } else if (type.equals("R*")) {
                position = Integer.parseInt(array[1]);
            } else if (array.length == 2) {
                number = Integer.parseInt(array[1]);
            }
            try {
                switch(type) {
                    case"II":
                        pkmns.insertStart(pokemons.get(number - 1));
                        break;
                    case"I*":
                        pkmns.insert(pokemons.get(number-1), position);
                        break;
                    case"IF":
                        pkmns.insertEnd(pokemons.get(number - 1));
                        break;
                    case"RI":
                        System.out.println("(R) " + pkmns.removeStart().getName());
                        break;
                    case"R*":
                        System.out.println("(R) " + pkmns.remove(position).getName());
                        break;
                    case"RF":
                        System.out.println("(R) " + pkmns.removeEnd().getName());
                        break;
                }
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
        }

        pkmns.show();

        sc.close();
    }
}