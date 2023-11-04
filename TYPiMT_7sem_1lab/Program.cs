using System.Text;
using DataDKA;

class Program
{
    static void Main()
    {
        string inputFile = "input.txt";
        string outputFile = "output.txt";

        string result = IsValidCCode(inputFile);

        File.WriteAllText(outputFile, result);
    }

    
    public readonly static string[] typesVar = {"int", "float", "double", "char", "long", "short"};

    public static readonly string[] two_types = {"long int", "int long", "short int", "int short", "double long", "long double"};

    static string IsValidCCode(string inputFile)
    {
        string allText = "";

        try{
            allText = File.ReadAllText(inputFile) + "\0";
        }catch (Exception e){
            Console.WriteLine("Ошибка: {0}", e.Message);
        }

        int i = 0, row = 0, colum, posSimbol = 0;
        string two_types_str = "";
        StringBuilder varName = new();
        HashSet<string> listVar= new();

        string stat, action;
        foreach(char simbol in allText){
            if (simbol == '\n'){
                i++;
                posSimbol = 0;
            }

            posSimbol++;

            try{
                colum = MyDataDKA.alfabet[simbol];
            }catch{
                return $"Ошибка:\nСтрока {i+1} позиция {posSimbol}\nДанный символ не разрешён алфавитом";
            }
            stat = MyDataDKA.delta[row, colum, 0];
            action = MyDataDKA.delta[row, colum, 1];

            if (stat == "ERROR")
                return $"Ошибка:\nСтрока {i+1} позиция {posSimbol}\nНе правильная конфигурация определения идентификатора\n{stat}:{action}";

            if (stat == "HALT")
                return "Описание корректно";
            
            string result = Situasion(action, ref varName, simbol, ref two_types_str, i, posSimbol, ref listVar, stat);

            if (result != "")
                return result;

            row = MyDataDKA.state[stat];
        }
        return "Неизвестная ситуация";
    }

    static string Situasion(string action, ref StringBuilder varName, char simbol, ref string two_types_str, int i, int posSimbol, ref HashSet<string> listVar, string stat){
        if (action == "A1")
            varName.Append(simbol);

        if (action == "A2")
            if (typesVar.Contains(varName.ToString())){
                two_types_str = varName.ToString();
                varName = new();
            }
            else
                return $"Ошибка:\nСтрока {i+1} позиция {posSimbol}\nТакой тип данных не зарегестрирован\n{stat}:{action}";

        if (action == "A3"){
            if (typesVar.Contains(varName.ToString())){
                two_types_str += " " + varName.ToString();
                if (two_types.Contains(two_types_str))
                    two_types_str = "";
                else 
                    return $"Ошибка:\nСтрока {i+1} позиция {posSimbol}\nТакой тип данных не зарегестрирован\n{stat}:{action}";
                varName = new();
            }
            else
                return $"Ошибка:\nСтрока {i+1} позиция {posSimbol}\nТакой тип данных не зарегестрирован\n{stat}:{action}";
        }
        
        if (action == "A4"){
            if (!typesVar.Contains(varName.ToString()))
                if (listVar.Add(varName.ToString()))
                    varName = new();
                else
                    return $"Ошибка:\nСтрока {i+1} позиция {posSimbol}\nпеременная с таким названием ({varName}) уже существует\n{stat}:{action}";
            else 
                return $"Ошибка:\nСтрока {i+1} позиция {posSimbol}\nидентификатор совпадает с типом данных ({varName})\n{stat}:{action}";
        }
        
        return "";
            
    }
}