// MI MAIN NO VA BIEN DEL TODO :( 
///*
// * File:   main.cpp
// * Author: MP-team 
// * @warning To be implemented by students. Follow the instructions given in the headers
// */
//
///**
// * @brief This program must load a sample dataset given as parameters to the program.
// * 
// * The main() function has three mandatory parameters:  
// * "-input <input_file>"  "-events <number_events>"  "-index-by Brand|UserID"
// *    - input_file is the path to the file used as input
// *    - number_events is the number of events to be read from the input_file
// *    - Brand and UserID with the parameter index-by marks the field used to build
// *      the index
// *  there are also three optional parameters:
// * "-report-by Brand|UserID|Type|Datetime"  "-output <output_file>"  "-display Framed|Fancy"
// *    - report-by marks the column used for grouping the event when creating the reports
// *    - output_file is the file to store the output
// *    - display is used to choose the format of the DataTable output:
// *  *  * - If the parameter is absent, the report is shown in plain text, using DataTable::showPlainReportH(0)
// *  *  * - If the parameter is set to Framed, the report is shown using a table format, with DataTable::showFramedReportH(0)
// *  *  * - If the parameter is set to Fancy, the report is shown as histograms using an external library, with DataTable::showFancyReportH(0)
// * 
// * ALL THE PARAMETERS CAN BE GIVEN IN ANY ORDER
// * 
// * The following calls are correct and equivalent
// * shopping3 -input_file data/ECommerce41.dataset -events 30 -index-by Brand -report-by Brand -display Framed
// * shopping3 -events 30 -display Framed -report-by Brand -input_file data/ECommerce41.dataset -index-by Brand 
// *
// */
//
///**
// * NOTE: NO PARAMETERS EXECUTION
// * In order to modularize the development of this assignment, a simplified execution
// * mode is proposed, where only one parameter is employed. The execution of the
// * program using:
// * 
// * shopping3 -noargs
// * 
// * is intended to be used with input redirection. 
// * To this end, several input files have been prepared. They are placed in folder
// * tests/validation, with name <dataset.keyboard>. This files always contain the
// * same structure:
// * - Path to the input file
// * - Number of events to read from input
// * - Field used to build the index (Brand or UserID)
// * - Field used to group the reports (Brand, UserID, Type or DateTime)
// * 
// * The proper way to call the program using this structure is the following (using
// * ECommerce30.keyboard as input, for example)
// * dist/Debug/GNU-Linux/shopping3 -noargs < tests/validation/ECommerce30.keyboard
// */
//
//#include <string>
//#include <cassert>
//#include <iostream>
//#include <fstream>
//#include "Event.h"
//#include "EventSet.h"
//#include "Index.h"
//#include "DataVector.h"
//#include "MPTests.h"
//
//#define ERROR_ARGUMENTS 1
//#define ERROR_OPEN 2
//#define ERROR_DATA 3
//
//using namespace std;
//
//
///**
// * @brief Update the counter per week day (value in 0..6) for every event found.
// * It also shows the computed values on the screen
// * @param evSet an input EventSet  
// * @param arrayA an int output array
// */
//void computeActivity(EventSet & evSet, int arrayA[]);
//
///**
// * @brief Breaks the program execution if an error is encountered during execution
// * @param errorcode Integer marking the type of error encountered (1 for arguments
// * error, 2 for open file error and 3 for data reading error, see ERROR_ARGUMENTS,
// * ERROR_OPEN and ERROR_DATA definitions above)
// * @param errordata String representing where the error has been produced (mainly
// * used to indicate the file that produced the error)
// */
//void errorBreak(int errorcode, string errordata);
//
///**
// * @brief Given anEventSet and a filtered Index over that dataset, build the
// * Event set with only the indexed events
// * @param es The original EventSet
// * @param indx The reduced Index
// * @return The subset of the EventSet referenced by the Index
// */
//EventSet extractEventSet(EventSet & es, Index & indx);
//
///**
// * @brief Helper function that prints information about main parameters when the
// * program is not called properly. Should be called from @see errorBreak when the
// * errorcode is equal to 1
// */
//void showHelp();
///**
// * Se asume fichero de entrada con el siguiente formato
// * primera linea un entero y un double
// * Siguientes lineas con cadenas tipo texto
// * ej:
// * 5 2.143
// * asdf, adfaf, adfaf,
// * sads asdf,asdfa adf,asdf,afaf
// * asdf,as,as,124,355,afra,35
// * @param name
// */
//void leerFichero(const string & name){
//    ifstream fent(name);
//    int n;
//    double d;
//    
//    string cadena;
//    if (fent.is_open()){
//        fent >> n >> d;
//        cout <<"->  "<< n << " "<< d<<endl;  
//        fent.ignore(); // saltamos el salto de linea (caracter que no se leyo) 
//        while (getline(fent,cadena)){
//             cout << "->  "<< cadena << endl;
//        }
//         cout << "Fichero leido"<<endl;
//
//    } else {
//        cout << "problemas con el fichero "<< name << endl;
//    }
//    fent.close();
//}
///**
// * Main block of the program. The full explanation of the behavior is given in
// * the comment above
// * @param argc Number of arguments passed to main
// * @param argv Strings representing those arguments
// * @return 
// */
//
//int main(int argc, char** argv) {
//    
////    DateTime defaultd;
////    std::string date = "2021-02-04 16:59:00 UTC";
////    DateTime today;
////    today.set("2021-02-04 16:59:00 UTC");
////    bool what;
////    cout << defaultd.isBefore(defaultd) << endl;
////    cout << defaultd.isBefore(today) << endl;
////    cout << today.isBefore(defaultd) << endl;
////    cout << today.sameDay(today) << endl;
////    cout << today.sameDay(date) << endl;
////    exit(0);
//    
////    SKIP_ASSERT_FALSE_R(defaultd.isBefore(defaultd)) << "A DateTime cannot be before itself"<<endl;
////    SKIP_ASSERT_TRUE_R(defaultd.isBefore(today)) << "Default date is before  today"<<endl;
////    SKIP_ASSERT_FALSE_R(today.isBefore(defaultd)) << "Today is not before the  Default date"<<endl;
//    
//// 0.- Example of file reading BORRAR.
//    
////    string exFilename = "./data/.ECommerce162-hit.dataset"; // nombre de fichero de prueba
////    leerFichero(exFilename);
//    
//    string ifilename = "", ofilename = "", indexby = "", reportby = "";
//    int n2Read;
//    string curr_arg;
//    ifstream ifile;
//    ofstream ofile;
//    
//    // 1.- Read the input arguments from argv
//    // -input <input_file> -events <number_events> -index-by UserID|Brand
//    //[-report-by UserID|Brand|Type|DateTime -output <output_file>
//    //-display Framed|Fancy]
//    
//    bool noargs = false, existe_input = false;
//    string modo_display = "Plain";
//    
//    for (int i = 1; i < argc && noargs == false; i++) { 
//        curr_arg = argv[i];
//        if (curr_arg == "-noargs") {
//            i++;
//            noargs = true; // Si no hay argumentos en el main se corta el bucle para seguir comprobando.
//        } else if (curr_arg == "-input") {
//            i++; // Para que pase al siguiente string de argv que tiene el archivo.
//            ifilename = argv[i]; // Metemos el archivo.
//            existe_input = true; // Indicamos que lo hemos añadido.
//        } else if (curr_arg == "-output") {
//                i++;
//                ofilename = argv[i];
//        } else if (curr_arg == "-events") {
//            i++;
//            try {
//                n2Read = stoi(argv[i]);
//            } catch (...) {
//                errorBreak(ERROR_ARGUMENTS, "");
//            } // Pues puede que al hacer stoi se produzca un fallo si no se da un número como argumento.
//        } else if (curr_arg == "-index-by") {
//            i++;
//            curr_arg = argv[i];            
//            if (curr_arg == "Brand" || curr_arg == "UserID") {
//                indexby = argv[i];
//            } else {
//                errorBreak(ERROR_ARGUMENTS, "");
//            } 
//        } else if (curr_arg == "-report-by") {
//            i++;
//            curr_arg = argv[i];
//            if (curr_arg == "UserID" || curr_arg == "Brand" || curr_arg =="DateTime")
//                reportby = argv[i];
//            else 
//                errorBreak(ERROR_ARGUMENTS, "");
//        } else if (curr_arg == "-display") {
//            i++;
//            modo_display = argv[i];
//            if (modo_display != "Framed" && modo_display != "Fancy") {
//                errorBreak(ERROR_ARGUMENTS, "");
//            }
//        }  else
//            errorBreak(ERROR_ARGUMENTS, "");
//    }
////   
//    // 2.- If the execution is a non-argument execution, read information from
//    // cin, else check that the arguments provided are correct
//    
//    if (noargs) {
//        cout << endl << "Please type the input file name: ";
//        cin >> ifilename;
//        cout << endl << "Please type the number of records to read: ";
//        cin >> n2Read;
//        cout << "Please select the field to index for (UserID, Brand): ";
//        cin >> indexby;
//        cout << endl << "Please select the field to filter with (DateTime, UserID, Brand, Type): ";
//        cin >> reportby;
//        cout << endl << "Please indicate the output file (empty for no output file): ";
//        cin >> ofilename;
//    } else {
//        if (!existe_input)
//            errorBreak(ERROR_ARGUMENTS, "");
//    } // Si no hemos metido ningún input en ninguno de los argumentos, se genera un error.
//    
//    // 3.- Try to open the proposed input file
//
//    ifile.open(ifilename);
//    if (!ifile.is_open()) {
//        errorBreak(ERROR_OPEN, ifilename);
//    } // Comprobamos que el archivo del que hacemos input se ha abierto correctamente.
//    
//    // 4.- Read the events from the input file and load them in a EventSet.
//    //     Only the correct ones will be charged on the EventSet
//
//    EventSet originalES;
//    
//    for (int i = 0; i < n2Read; i++) {
//        string line;
//        getline(ifile, line);
//        Event evento(line);
//        if (!evento.isEmpty()) 
//            originalES.add(evento);   
//         else 
//            errorBreak(ERROR_DATA, ifilename);
//    }
//        
//    ifile.close();
//    
//    // 5.- Build the main index, depending on the input argument
//
//    Index indx;
//    int int_indexby;
//    if (indexby == "Brand")
//        int_indexby = 1;
//    else 
//        int_indexby = 0;
//    // Vemos donde construimos el Index dependiendo de -index-by
//    
//    indx.build(originalES, int_indexby);  // Construimos el indice con el eventset del apartado 4.
//
//    // 6.- Print the amount of events read and events indexed. Keep in mind that
//    // the size of the index can be lesser than the size of the EventSet, since
//    // the Events with empty Brand cannot be indexed
//    
//    cout << "Events read: " << originalES.size() << endl;
//    cout << "Events indexed: " << indx.size() << endl;
//
//    // 7.- Filter the original EventSet using the main Index. The filtered EventSet
//    // will contain only the indexed Events (if the Index is built by user, the
//    // original and the filtered EventSets will be identical, since every event
//    // must have an associated UserID. If the index is built by brand, the filtered
//    // EventSet can be smaller than the original dataset, since there are Events
//    // without Brand, which cannot be indexed
//
//    EventSet filteredES = extractEventSet(originalES, indx); // Ver si vuelvo a hacer index.build
//    indx.build(filteredES, int_indexby);
//    
//    // 8.- Compute activity by weekday
//    
//    int arrayA[7];
//    computeActivity(filteredES, arrayA);
//    
//    DataVector weeklyReport(7);
//    weeklyReport.setTitle("Report Week Activity");
//    weeklyReport.loadLabels(DAYNAME);
//    weeklyReport.loadValues(arrayA);
//    
//    // 9.- Generate reports (traffic and money amount) grouped by the corresponding
//    // field (indicated by parameter -report-by, Brand by default). Also, save
//    // the value, the amount of traffic and the index of the element that generated
//    // most traffic
//    
//    string values[MAXEVENT];
//    int traffic[MAXEVENT];
//    double amount[MAXEVENT];
//    int n_values = 0; // Numero de elementos diferentes.
//    EventSet aux_es;
//    Index aux_indx;
//   
//    findUnique(filteredES, reportby, values, n_values);
//    
//    for (int i = 0; i < n_values; i++) {
//        if (reportby == "Brand" || reportby == "UserID") {
//            aux_indx = rawFilterIndex(filteredES, indx, reportby, values[i]); // Indice por cada elemento diferente.
//            traffic[i] = aux_indx.size(); // Número de veces que se repite cada elemento.
//            amount[i] = sumPrice(filteredES, aux_indx); // Precio generado por cada elemento.
//        } else {
//            for (int i = 0; i < n_values; i++) {
//                aux_es = rawFilterEvents(filteredES, reportby, values[i]);
//                traffic[i] = aux_es.size();
//                amount[i] = sumPrice(aux_es);
//            }
//        } // Caso para DateTime (no se puede generar un index) AQUI CREO QUE FALLA 
//        // ALGO POR EL TEST _01_Basics.Integrated_5_records.
//    }
//
//    int max_pos = 0;
//    for (int i = 0; i < n_values; i++) {
//        if (traffic[max_pos] < traffic[i]) {
//            max_pos = i;
//        }
//    } // Obtenemos la posición del elemento que más se repite.
//    
//    Index more_traffic_index = rawFilterIndex(filteredES, indx, reportby, values[max_pos]); // Generamos el índice con 
//    // el elemento que más se repite.
//    
//    DataVector hitsData(n_values);
//    hitsData.setTitle("Report traffic");
//    hitsData.loadLabels(values);
//    hitsData.loadValues(traffic);
//
//    DataVector amountData(n_values);
//    amountData.setTitle("Report amount");
//    amountData.loadLabels(values);
//    amountData.loadValues(amount);
//    
//    // 10.- Display information, depending on the display mode specified by
//    // -display (Plain mode by default). Also, print the information about the
//    // element with highest traffic (its value and the number of events generated)
//    
//    if(modo_display == "Framed") {
//        cout << weeklyReport.showFramedReportV() << endl;
//        cout << hitsData.showFramedReportV(0) << endl;
//        cout << amountData.showFramedReportV(0) << endl;
//    } else if (modo_display == "Fancy") {
//        cout << weeklyReport.showFancyReportV() << endl;
//        cout << hitsData.showFancyReportV(0) << endl;
//        cout << amountData.showFancyReportV(0) << endl;
//    } else {
//        cout << weeklyReport.showPlainReportV() << endl;
//        cout << hitsData.showPlainReportV(0) << endl;
//        cout << amountData.showPlainReportV(0) << endl;
//    }
//
//    // 11. Save the EventSet corresponding to the element with highest traffic in
//    // the output file, if specified
//    
//    ofile.open(ofilename);
//    if (ofilename != "" && ofilename != "empty") {
//        if (ofile.is_open()) {
//            filteredES.write(ofile);
//        } else {
//            errorBreak(ERROR_OPEN, ofilename);
//        }
//    }
//    
//    // 12.- Report everything to the tests suite using REPORT_DATA2
//     REPORT_DATA2(originalES, "Original read from dataset");
//     REPORT_DATA2(filteredES, "Events indexed");
//     REPORT_DATA2(hitsData, "Report traffic");
//     REPORT_DATA2(amountData, "Report amount");
//
//    return 0;
//    
//////////////////////////////////////////////////////////////////////////////////
//    
//    // NO HACER CASO: usado para hacer debug del upper_bound
//    
////    Pair pair0, pair1, pair2, pair3, pair4, pair5;
////    
////    pair0.set("ccc",0);
////    pair1.set("ccc",3);
////    pair2.set("aaa", 0);
////    pair3.set("bbb",1);
////    pair4.set("aaa",2);
////    pair5.set("ddd",1);
////    
////    Index prueba;
////    prueba.add(pair0);
////    prueba.add(pair1);
////    prueba.add(pair2);
////    prueba.add(pair3);
////    prueba.add(pair4);
////    prueba.add(pair5);
////    
////
////     for (int i = 0; i < prueba.size(); i++){
////         cout << prueba.at(i).to_string()  << endl;
////     }
//    
//////////////////////////////////////////////////////////////////////////////////////////
//    
//}
//
//void errorBreak(int errorcode, string errordata) {
//    if (errorcode == ERROR_ARGUMENTS) {
//        CVAL << "Error in call" << endl;
//        showHelp();
//        std::exit(-1);
//    } else if (errorcode == ERROR_DATA) {
//        CVAL << "Data error in file " + errordata << endl;
//        std::exit(-1);
//    } else if (errorcode == ERROR_OPEN) {
//        CVAL << "Error opening file " + errordata << endl;
//        std::exit(-1);
//    }
//}
//
//void computeActivity(EventSet & evSet, int arrayA[]) {
//    DateTime fecha;
//    Event eventos;
//    
//    for(int i = 0; i < 7; i++)
//        arrayA[i] = 0; // Inicializo el vector a 0.
//    
//    for(int i = 0; i < evSet.size(); i++){
//        eventos.set((evSet.at(i)).to_string());
//        fecha = eventos.getDateTime(); 
//        arrayA[fecha.weekDay()]++;
//    }        
//    
//    cout << "Activity found:";
//    for (int day = 0; day < 7; day++) {
//        cout << " " << DAYNAME[day] << "(" <<arrayA[day] << ")";
//    }
//    cout << endl;
//}
//
//EventSet extractEventSet(EventSet & es, Index & indx) {
//    EventSet eventos_filtrados;
//    for (int i = 0; i < indx.size(); i++)
//        eventos_filtrados.add(getEvent(es, indx, i));
//    
//    return eventos_filtrados;
//}
//
//void showHelp() {
//    cout << "Please use: -input <filename> -events <number> -index-by UserID|Brand [-report-by UserID|Brand|Type|DateTime -output <filename>]" << endl;
//    cout << "\n-input <filename>\n\tRead events from dataset in <filename>";
//    cout << "\n-events <number>\n\tNumber of events to read";
//    cout << "\n-index-by <field>\n\tField to index by. It can only be UserID or Brand";
//    cout << "\n\nOptional arguments";
//    cout << "\n-report-by <field>\n\tField to report by. It can only be UserID, Brand, Type or DateTime. The default value is Brand";
//    cout << "\n-output <filename>\n\tFile to save the dataset of the field selected with -index-by with maximum traffic. If not specified, it does not save anything" << endl << endl;
//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * File:   main.cpp
 * Author: MP-team 
 * @warning To be implemented by students. Follow the instructions given in the headers
 */

/**
 * @brief This program must load a sample dataset given as parameters to the program.
 * 
 * The main() function has three mandatory parameters:  
 * "-input <input_file>"  "-events <number_events>"  "-index-by Brand|UserID"
 *    - input_file is the path to the file used as input
 *    - number_events is the number of events to be read from the input_file
 *    - Brand and UserID with the parameter index-by marks the field used to build
 *      the index
 *  there are also three optional parameters:
 * "-report-by Brand|UserID|Type|Datetime"  "-output <output_file>"  "-display Framed|Fancy"
 *    - report-by marks the column used for grouping the event when creating the reports
 *    - output_file is the file to store the output
 *    - display is used to choose the format of the DataTable output:
 *  *  * - If the parameter is absent, the report is shown in plain text, using DataTable::showPlainReportH(0)
 *  *  * - If the parameter is set to Framed, the report is shown using a table format, with DataTable::showFramedReportH(0)
 *  *  * - If the parameter is set to Fancy, the report is shown as histograms using an external library, with DataTable::showFancyReportH(0)
 * 
 * ALL THE PARAMETERS CAN BE GIVEN IN ANY ORDER
 * 
 * The following calls are correct and equivalent
 * shopping3 -input_file data/ECommerce41.dataset -events 30 -index-by Brand -report-by Brand -display Framed
 * shopping3 -events 30 -display Framed -report-by Brand -input_file data/ECommerce41.dataset -index-by Brand 
 *
 */

/**
 * NOTE: NO PARAMETERS EXECUTION
 * In order to modularize the development of this assignment, a simplified execution
 * mode is proposed, where only one parameter is employed. The execution of the
 * program using:
 * 
 * shopping3 -noargs
 * 
 * is intended to be used with input redirection. 
 * To this end, several input files have been prepared. They are placed in folder
 * tests/validation, with name <dataset.keyboard>. This files always contain the
 * same structure:
 * - Path to the input file
 * - Number of events to read from input
 * - Field used to build the index (Brand or UserID)
 * - Field used to group the reports (Brand, UserID, Type or DateTime)
 * 
 * The proper way to call the program using this structure is the following (using
 * ECommerce30.keyboard as input, for example)
 * dist/Debug/GNU-Linux/shopping3 -noargs < tests/validation/ECommerce30.keyboard
 */

#include <string>
#include <cassert>
#include <iostream>
#include <fstream>
#include "Event.h"
#include "EventSet.h"
#include "Index.h"
#include "DataVector.h"
#include "MPTests.h"

#define ERROR_ARGUMENTS 1
#define ERROR_OPEN 2
#define ERROR_DATA 3

using namespace std;


/**
 * @brief Update the counter per week day (value in 0..6) for every event found.
 * It also shows the computed values on the screen
 * @param evSet an input EventSet  
 * @param arrayA an int output array
 */
void computeActivity(const EventSet & evSet, int arrayA[]);

/**
 * @brief Breaks the program execution if an error is encountered during execution
 * @param errorcode Integer marking the type of error encountered (1 for arguments
 * error, 2 for open file error and 3 for data reading error, see ERROR_ARGUMENTS,
 * ERROR_OPEN and ERROR_DATA definitions above)
 * @param errordata String representing where the error has been produced (mainly
 * used to indicate the file that produced the error)
 */
void errorBreak(int errorcode, const string & errordata);

/**
 * @brief Given anEventSet and a filtered Index over that dataset, build the
 * Event set with only the indexed events
 * @param es The original EventSet
 * @param indx The reduced Index
 * @return The subset of the EventSet referenced by the Index
 */
EventSet extractEventSet(const EventSet & es, const Index & indx);

/**
 * @brief Helper function that prints information about main parameters when the
 * program is not called properly. Should be called from @see errorBreak when the
 * errorcode is equal to 1
 */
void showHelp();

/**
 * Main block of the program. The full explanation of the behavior is given in
 * the comment above
 * @param argc Number of arguments passed to main
 * @param argv Strings representing those arguments
 * @return 
 */
int main(int argc, char** argv) {

    string ifilename = "", ofilename = "", indexby = "", reportby = "";
    string sarg;
    int n2Read = -1, nEvents = 0;
    ifstream ifile;
    ofstream ofile;
    EventSet originalES, filteredES, bestES;
    Index mainIndex, filteredIndex, bestIndex;
    // Report
    bool noargs = false;
    double dcounter[MAXEVENT];
    int icounter[MAXEVENT], nlabels, bestValue;
    string labels[MAXEVENT], bestLabel;
    DataVector weeklyData, hitsData, amountData;
    string display = "Plain";

    // 1.- Process the input arguments
    for (int i = 1; i < argc;) { // load of the arguments
        sarg = argv[i];
        if (sarg == "-input") {
            i++;
            if (i >= argc) errorBreak(ERROR_ARGUMENTS, "");
            ifilename = argv[i++];
        } else if (sarg == "-output") {
            i++;
            if (i >= argc) errorBreak(ERROR_ARGUMENTS, "");
            ofilename = argv[i++];
        } else if (sarg == "-report-by") {
            i++;
            if (i >= argc) errorBreak(ERROR_ARGUMENTS, "");
            reportby = argv[i++];
        } else if (sarg == "-index-by") {
            i++;
            if (i >= argc) errorBreak(ERROR_ARGUMENTS, "");
            indexby = argv[i++];
        } else if (sarg == "-events") {
            i++;
            if (i >= argc) errorBreak(ERROR_ARGUMENTS, "");
            n2Read = atoi(argv[i++]);
        } else if (sarg == "-display") {
            i++;
            if (i >= argc) errorBreak(ERROR_ARGUMENTS, "");
            display = argv[i++];
        } else if (sarg == "-noargs") {
            i++;
            noargs = true;
        } else
            errorBreak(ERROR_ARGUMENTS, ""); // any other parameters
    } // end check syntax

    
    // 2.- If the execution is a non-argument execution, read information from
    // cin
    if (!noargs) {
        // Process arguments
        if (reportby == "")
            reportby = "Brand";

        if (n2Read < 0 || ifilename == "" || indexby == "" ||
                (indexby != "UserID" && indexby != "Brand") ||
                (reportby != "Brand" && reportby != "UserID" && reportby != "Type" && reportby != "DateTime"))
            errorBreak(ERROR_ARGUMENTS, "");
    } else {
        cout << endl << "Please type the input file name: ";
        cin >> ifilename;
        cout << endl << "Please type the number of records to read: ";
        cin >> n2Read;
        cout << "Please select the field to index for (UserID, Brand): ";
        cin >> indexby;
        cout << endl << "Please select the field to filter with (DateTime, UserID, Brand, Type): ";
        cin >> reportby;
        cout << endl << "Please indicate the output file (empty for no output file): ";
        cin >> ofilename;
    }
    
    // 3.- Try to open the proposed input file
    ifile.open(ifilename); // ifilename != ""  already check 
    if (!ifile) {
        errorBreak(ERROR_OPEN, ifilename);
    }
    cout << endl << "Reading from " << ifilename << endl;

    // 4.- Read the events from the input file and load them in a EventSet.
    //     Only the correct ones will be charged on the EventSet
    if (!originalES.read(ifile, n2Read)) {
        errorBreak(ERROR_DATA, ifilename);
    }

    // 5.- Build the main index, depending on the input argument
    if (indexby == "UserID") {
        mainIndex.build(originalES, 0);
    } else {
        mainIndex.build(originalES, 1);
    }

    // 6.- Print the amount of events read and events indexed. Keep in mind that
    // the size of the index can be lesser than the size of the EventSet, since
    // the Events with empty Brand cannot be indexed
    cout << endl << "Read " << originalES.size() << " records from file " << ifilename;
    cout << endl << "Main Index by " << indexby << endl << mainIndex.size() << " pairs ";
    if (originalES.size() != mainIndex.size()) {
        cout << endl << originalES.size() - mainIndex.size() << " records could not be indexed";
    }

    // 7.- Filter the original EventSet using the main Index. The filtered EventSet
    // will contain only the indexed Events (if the Index is built by user, the
    // original and the filtered EventSets will be identical, since every event
    // must have an associated UserID. If the index is built by brand, the filtered
    // EventSet can be smaller than the original dataset, since there are Events
    // without Brand, which cannot be indexed
    filteredES = extractEventSet(originalES, mainIndex);
    cout << endl << "amount :" << sumPrice(originalES, mainIndex) << endl;

    // 8.- Compute activity by weekday
    cout << endl;
    computeActivity(filteredES, icounter);

    weeklyData.alloc(7);
    weeklyData.setTitle("Events/day");
    weeklyData.loadLabels(DAYNAME);
    weeklyData.loadValues(icounter);
    cout << endl << weeklyData.showFancyReportH(0) << endl;
    cout << endl << weeklyData.showFramedReportH(0) << endl;
    cout << endl << weeklyData.showPlainReportH(0) << endl;


    // 9.- Generate reports (traffic and money amount) grouped by the corresponding
    // field (indicated by parameter -report-by, Brand by default). Also, save
    // the value, the amount of traffic and the index of the element that generated
    // most traffic
    findUnique(filteredES, reportby, labels, nlabels);

    // Traffic & Amount
    bestValue = -1;
    for (int i = 0; i < nlabels; i++) {
        filteredIndex = rawFilterIndex(originalES, mainIndex, reportby, labels[i]);
        icounter[i] = filteredIndex.size();
        if (icounter[i] > bestValue) {
            bestValue = icounter[i];
            bestIndex = filteredIndex;
            bestLabel = labels[i];
        }
        dcounter[i] = sumPrice(originalES, filteredIndex);
    }

    hitsData.alloc(nlabels);
    hitsData.setTitle(reportby + " (traffic)");
    hitsData.loadLabels(labels);
    hitsData.loadValues(icounter);

    amountData.alloc(nlabels);
    amountData.setTitle(reportby + " (amount)");
    amountData.loadLabels(labels);
    amountData.loadValues(dcounter);
    
    // 10.- Display information, depending on the display mode specified by
    // -display (Plain mode by default). Also, print the information about the
    // element with highest traffic (its value and the number of events generated)
    if (display == "Fancy") {
        cout << endl << weeklyData.showFancyReportH(0) << endl;
        cout << endl << hitsData.showFancyReportH(0) << endl;
        cout << endl << amountData.showFancyReportH(0) << endl;
    } else if (display == "Framed") {
        cout << endl << weeklyData.showFramedReportH(0) << endl;
        cout << endl << hitsData.showFramedReportH(0) << endl;
        cout << endl << amountData.showFramedReportH(0) << endl;
    } else {
        cout << endl << weeklyData.showPlainReportH(0) << endl;        
        cout << endl << hitsData.showPlainReportH(0) << endl;        
        cout << endl << amountData.showPlainReportH(0) << endl;
    }
    cout << endl << "Highest traffic choice (" << bestLabel << ") with " << bestValue << " hits " << endl;

    // 11. Save the EventSet corresponding to the element with highest traffic in
    // the output file, if specified
    if (ofilename != "") {
        cout << endl << "Saving on " << ofilename << endl;
        ofile.open(ofilename);
        if (!ofile) {
            errorBreak(ERROR_OPEN, ofilename);
        }
        write(ofile, originalES, bestIndex);
        cout << extractEventSet(originalES, bestIndex).to_string();
        ofile.close();
    }
    
    // 12.- Report everything to the tests suite using REPORT_DATA2
    
    REPORT_DATA2(originalES, "Original read from dataset");
    REPORT_DATA2(filteredES, "Events indexed");
    REPORT_DATA2(hitsData, "Report traffic");
    REPORT_DATA2(amountData, "Report amount");

    return 0;
}

void errorBreak(int errorcode, const string & errordata) {
    switch (errorcode) {
        case ERROR_ARGUMENTS:
            CVAL << endl <<"Error in call" << endl;
            showHelp();
            break;
        case ERROR_OPEN:
            CVAL << endl << "Error opening file " << errordata << endl;
            break;
        case ERROR_DATA:
            CVAL << endl <<"Data error in file " << errordata << endl;
            break;
    }
    std::exit(1);
}

void computeActivity(const EventSet & evSet, int arrayA[]) {
    for (int day = 0; day < 7; day++) {
        arrayA[day] = 0;
    }
    for (int i = 0; i < evSet.size(); i++) {
        arrayA[evSet.at(i).getDateTime().weekDay()] += 1;
    }
    cout << "Activity found:";
    for (int day = 0; day < 7; day++) {
        cout << " " << DAYNAME[day] << "(" << arrayA[day] << ")";
    }
    cout << endl;
}

EventSet extractEventSet(const EventSet & es, const Index & indx) {
    EventSet res;

    for (int i = 0; i < indx.size(); i++) {
        res.add(es.at(indx.at(i).getPos()));
    }
    return res;
}

void showHelp() {
    cout << "Please use: -input <filename> -events <number> -index-by UserID|Brand [-report-by UserID|Brand|Type|DateTime -output <filename>]" << endl;
    cout << "\n-input <filename>\n\tRead events from dataset in <filename>";
    cout << "\n-events <number>\n\tNumber of events to read";
    cout << "\n-index-by <field>\n\tField to index by. It can only be UserID or Brand";
    cout << "\n\nOptional arguments";
    cout << "\n-report-by <field>\n\tField to report by. It can only be UserID, Brand, Type or DateTime. The default value is Brand";
    cout << "\n-output <filename>\n\tFile to save the dataset of the field selected with -index-by with maximum traffic. If not specified, it does not save anything" << endl << endl;
}