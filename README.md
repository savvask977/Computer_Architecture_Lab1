# Αρχιτεκτονική Προηγμένων Υπολογιστών 


## **Εργαστηριακή Άσκηση 1**  
**Καράμπελας Σάββας, ΑΕΜ: 9005**  
**Καράμπελας Νίκος, ΑΕΜ: 8385**  

Έχοντας εγκαταστήσει τα απαραίτητα εργαλεία και έχοντας κάνει build την έκδοση του **gem5** για **ARM** ISAs, τρέχουμε την εντολή:  

```bash
./build/ARM/gem5.opt -d results_hello configs/example/arm/starter_se.py --cpu="minor" "tests/test-progs/hello/bin/arm/linux/hello" # Hello world!
```

Η εντολή αυτή βασίζεται στην γενική μορφή εντολών που χρησιμοποιούμε για τον gem5 και είναι η εξής:

```bash
<gem5_binary> [gem5_options] <simulation_script> [script_options]
``` 
Τα αποτελέσματα αποθηκεύονται στο directory _results_hello_ και είναι τα εξής αρχεία: 

* **stats.txt**
* **config.ini**
* **config.json**

>
 >### Ερώτημα 1
 >
Ανατρέχοντας στο αρχείο starter_se.py μπορούμε να αντλήσουμε πληροφορίες σχετικά με τη δομή του συστήματος που προσομοιώνουμε. Το σύστημα αποτελείται από έναν επεξεργαστή και ένα υποσύστημα μνήμης και όχι από ένα πλήρες σύστημα. Παρατηρούμε ότι εάν παραλείψουμε να προσθέσουμε script options, δημιουργείται το σύστημα με κάποιες default τιμές. Αυτές είναι:  
* atomic CPU με ένα πυρήνα και συχνότητα λειτουργίας 4 GHz
* Μνήμη DDR3 1600 8X8
* 2 memory channels
* Φυσική Μνήμη 2 GB  
* Συχνότητα ρολογιού 1 GHz
* Voltage 3.3 V 
  
Ωστόσο, στη παραπάνω εντολή εμείς προσδιορίζουμε το τύπο της CPU(MinorCPU). Σημειώνεται ότι στο αρχείο starter_se.py έχουν προσδιοριστεί τρία μοντέλα CPU(_Atomic, Minor, HPI_), μαζί με τα προκαθορισμένα configurations του. Θα έχουμε τελικά τα παρακάτω χαρακτηριστικά:
* **MinorCPU** με ένα πυρήνα και συχνότητα λειτουργίας 1GHz
* Θα έχουμε δύο επίπεδα μνήμης cache(L1, L2) με καθορισμένο cache line size 64.
* **Walk Cache, L1D cache, L1I cache, L2 cache**
* **clock frequency** 1GHz 
* **Clock voltage** 3.3 V


 >### Ερώτημα 2
 
Α) Το σύστημα που προσομοιώνουμε λοιπόν, έχει τα παρακάτω χαρακτηριστικά τα οποία επιβεβαιώνουμε μέσω του αρχείου se.py:
* **MinorCPU** με ένα πυρήνα και συχνότητα λειτουργίας 1GHz
* Θα έχουμε δύο επίπεδα μνήμης cache(L1, L2) με καθορισμένο cache line size 64.
* **L1D cache**  
   * size: 32768
   * associativity: 2
   * data_latency: 2
   * response_latency: 1
   * read & write 
* **L1I cache**  
   * size: 49152
   * associativity: 3
   * data_latency: 1
   * response_latency: 1
   * read only
* **L2 cache**  
   * size: 1048576 
* 2 **DRAM** οι οποίες μέσω των ports συνδέονται με το membus στο οποίο είναι συνδεδεμένη και η L2 cache. 
* 2 **buses**, ένα που συνδέει την L2 cache με τις CPU caches(L1I, L1D) και ένα που συνδέει την L2 με την φυσική μνήμη. 



| **Παράμετρος**    | **Τιμή**         |
| ------------- | ------------- |
| CPU TYPE      | MinorCPU      | 
| Clock Rate    | 1 GHz |
| Clock Voltage | 3.3 V  |
| L1I Cache     |  49152  |
| L1D Cache     |  32768  |
| L2  Cache     |  1048576   |
| Cache Line Size     |  64  | 


Β) Από το αρχείο stats.txt έχουμε ότι το σύνολο των "committed" εντολών είναι **5028**. Η διαφορά στον αριθμό των εντολών που είναι commited από τον αριθμό των συνολικών εντολών στον gem5 που είναι 5834, οφείλεται στο γεγονός ότι αυτές οι παραπάνω εντολές είναι για να γίνει initialize η διαδικασία προσομοίωσης. 
 
C) Η L2 cache προσπελάστηκε **479** φορές όπως μας πληροφορεί το stats.txt με το πεδίο system.cpu_cluster.l2.overall_accesses::total. Θα μπορούσαμε να υπολογίσουμε τον αριθμό των προσπελάσεων της L2 εάν υπολογίζαμε τον αριθμό των εντολών που κάνουν hit στην cache L2 και τον αριθμό των εντολών που κάνουν miss και τους αθροίζαμε.

>### Ερώτημα 3 
   
##### **MinorCPU**  
Η MinorCPU είναι ένα in-order μοντέλο επεξεργαστή με fixed pipeline αλλά με παραμετροποιήσημες δομές δεδομένων. Δίνει τη δυνατοτήτα εκτέλεσης διαφοροποιώντας τις παραμέτρους προσομοίωσης. Για παράδειγμα, αλλαγή της συχνότητας λειτουργίας ή της τεχνολογίας μνήμης. Είναι ιδανική για τη μοντελοποίηση επεξεργαστών στους οποίους η εκτέλεση εντολών είναι αυστηρά in-order. Επιτρέπει την οπτικοποίηση της θέσης μιας εντολής που αποτελεί χρήσιμο εργαλείο. Τέλος, δεν υποστηρίζει multithreading.

##### **TimingSimpleCPU**  
Η TimingSimpleCPU είναι μοντέλο επεξεργαστή και ανήκει στη κατηγορία των SimpleCPUs. Δεν διαθέτει pipeline και αυτός είναι ο λόγος που για κάθε εντολή που απαιτεί πρόσβαση στη μνήμη αναγκάζεται να κάνει stall περιμένοντας το response. Είναι ιδανική για γρήγορες προσομοιώσεις μοντέλων που δεν απαιτούν λεπτομερή περιγραφή.

A) Στο ερώτημα αυτό γράφουμε ένα απλό σχετικά πρόγραμμα σε γλώσσα C, το οποίο θα χρησιμοποιήσουμε στην εκτέλεση του gem5. Θα χρησιμοποιήσουμε διαφορετικά μοντέλα CPU σε κάθε εκτέλεση αλλά οι υπόλοιπες παράμετροι θα διατηρούνται ίδιες. Έτσι, θα μπορέσουμε να διακρίνουμε τις διαφορές στα αποτελέσματα των δύο μοντέλων, όσον'αναφορά τους χρόνους εκτέλεσης. Για το build του gem5 θα έχουμε το configuration αρχείο se.py. Η εντολή που θα τρέξουμε θα έχει την εξής μορφή:    


```bash
./build/ARM/gem5.opt -d minor_results configs/example/se.py --cpu-type=MinorCPU --caches --cmd="myprog_arm"
```  
και για την TimingSimpleCPU:
```bash
./build/ARM/gem5.opt -d timing_results configs/example/se.py --cpu-type=TimingSimpleCPU --caches --cmd="myprog_arm"
```


| **CPU TYPE**       |  **Ταχύτητα Εκτέλεσης** |   
| -------------      | ------------- | 
| MinorCPU           |      1,051ms|          
| TimingSimpleCPU    |       2,390ms |  

Βλέπουμε δηλαδή ότι η MinorCPU χρειάζεται το μισό χρόνο για να εκτελέσει ένα απλό πρόγραμμα σε σχέση με την TimingSimple.  

B)Η έλειψη pipeline στη περίπτωση της TimingSimpleCPU ευθύνεται για το γεγονός ότι είναι πιο αργή σε σχέση με τη MinorCPU. Πιο συγκεκριμένα τα memory requests απαιτούν κάποιο χρόνο να φτάσουν στη μνήμη και επειδή δεν υπάρχει pipeline, η CPU αναγκάζεται να περιμένει για κάθε request στη μνήμη, το response πριν συνεχίσει. Αντιθέτως, η MinorCPU διαθέτει pipeline και δεν χρειάζεται να περιμένει το response για κάθε request μνήμης αλλά συνεχίζει με την εκτέλεση της επόμενης εντολής. Αυτό έχει ως αποτέλεσμα να έχει μικρότερο χρόνο εκτέλεσης.

C) Σε αυτό το βήμα θα αλλάξουμε μία παράμετρο του επεξεργαστή και θα παρατηρήσουμε ξανά τα αποτελέσματα που λαμβάνουμε για τα δύο μοντέλα. Πιο συγκεκριμένα, θα αλλάξουμε την συχνότητα λειτουργίας της CPU σε 0,1GHz και τη τεχνολογία της μνήμης που χρησιμοποιούμε σε DDR3_2133_8x8. Οι εντολές που τρέχουμε είναι οι παρακάτω και αμέσως μετά βρίσκονται τα αποτελέσματα που παρατηρήθηκαν.

```bash
./build/ARM/gem5.opt -d timing_results_freq configs/example/se.py --cpu-type=TimingSimpleCPU --cpu-clock="0.1GHz" --caches --cmd="myprog_arm" # TimingSimpleCPU
```    
```bash
./build/ARM/gem5.opt -d minor_results_freq configs/example/se.py --cpu-type=MinorCPU --cpu-clock="0.1GHz" --caches --cmd="myprog_arm" # MinorCPU 
```    
```bash
./build/ARM/gem5.opt -d minor_results_ddr3 configs/example/se.py --cpu-type=MinorCPU --caches --mem-type='DDR3_2133_8x8' --cmd="myprog_arm" # MinorCPU 
```
```bash
./build/ARM/gem5.opt -d timing_results_ddr3 configs/example/se.py --cpu-type=TimingSimpleCPU --caches --mem-type='DDR3_2133_8x8' --cmd="myprog_arm" 
 # TimingSimpleCPU
``` 

Αλλάζοντας τη **συχνότητα της CPU** σε 0,1GHz έχουμε:
   * MinoCPU : 20,394ms 
   * TimingSimpleCPU: 47,168ms  
     
άρα ο χρόνος εκτέλεσης αυξάνεται πολύ όταν μειώνουμε τη συχνότητα της CPU, κάτι που είναι λογικό και αναμενώμενο.

Αλλάζοντας τη **τεχνολογία μνήμης** σε DDR3 2133 8X8 έχουμε:  
   * MinoCPU : 1,049ms
   * TimingSimpleCPU:  2,388ms  
  
άρα ο χρόνος εκτέλεσης μειώνεται με αυτή τη τεχνολογία μνήμης.  

Στη συνέχεια τρέξαμε τις παρακάτω εντολές για τα δύο μοντέλα, μέσω των οποίων οι παράμετροι που αλλάζουμε είναι 
η συχνότητα λειτουργίας του συστήματος και το πρωτόκολλο μνήμης. Τα αποτελέσματα είναι αυτά που ακολουθούν.

```bash 
./build/ARM/gem5.opt -d timing_results_sysclock configs/example/se.py --cpu-type=TimingSimpleCPU --caches --cmd="myprog_arm" --sys-clock="2.5GHz" # TimingSimpleCPU
``` 
```bash 
./build/ARM/gem5.opt -d minor_results_sysclock configs/example/se.py --cpu-type=MinorCPU --caches --cmd="myprog_arm" --sys-clock="2.5GHz" # MinorCPU
``` 
```bash
./build/ARM/gem5.opt -d timing_results_ruby configs/example/se.py --cpu-type=TimingSimpleCPU --ruby --cmd="myprog_arm" # TimingSimpleCPU
``` 
```bash 
./build/ARM/gem5.opt -d minor_results_ruby configs/example/se.py --cpu-type=MinorCPU --ruby --cmd="myprog_arm" # MinorCPU
``` 
Αλλάζοντας τη **συχνότητα λειτουργίας του συστήματος** σε 2,5GHz έχουμε:
   * MinoCPU : 1,047ms 
   * TimingSimpleCPU: 2,385ms  
     
άρα ο χρόνος εκτέλεσης μειώνεται όταν αυξάνουμε τη συχνότητα λειτουργίας, κάτι που είναι λογικό και αναμενώμενο.

Αλλάζοντας το **πρωτόκολλο μνήμης** σε Ruby έχουμε:  
   * MinoCPU : 1,156ms
   * TimingSimpleCPU:  2,447ms  
  
άρα ο χρόνος εκτέλεσης αυξάνει με αυτό το πρωτόκολλο μνήμης.


>### Βιβλιογραφία - Πηγές 
1. [gem5 Documentation](https://www.gem5.org/documentation/learning_gem5/introduction/)
2. [gem5 TimingSimpleCPU](https://www.gem5.org/documentation/general_docs/cpu_models/SimpleCPU#timingsimplecpu)
3. [gem5 MinorCPU](https://www.gem5.org/documentation/general_docs/cpu_models/minor_cpu)
4. [In-Order vs Out-of-Order](https://courses.cs.washington.edu/courses/csep548/06au/lectures/introOOO.pdf)
5. [The gem5 Simulator Paper](https://www.cse.wustl.edu/~roger/560M.f17/p1-binkert.pdf)
6. [pages.cs.wisc-cpu.cc](http://pages.cs.wisc.edu/~swilson/gem5-docs/minor_2cpu_8cc_source.html)
7. [pages.cs.wisc-timing.cc](http://pages.cs.wisc.edu/~swilson/gem5-docs/timing_8cc_source.html)
8. [Markdown Tutorial](https://www.markdowntutorial.com/ )
9. [arm keil](https://www.keil.com/support/man/docs/armasm/armasm_dom1359731139484.htm)  

>### Αξιολόγηση Εργαστηριακής Άσκησης
Στη πρώτη αυτή εργασία κληθήκαμε να εξοικειωθούμε με τον gem5 και αρκετά ακόμα εργαλεία όπως είναι το git και η γλώσσα Markdown(στην οποία έχει γίνει και η συγγραφή της αναφοράς αυτής). Ξεκινώντας, θα θέλαμε να σημειώσουμε ότι οι οδηγίες εγκατάστασεις των απαιτούμενων πακέτων, για να υλοποιηθεί το build του gem5 είναι λεπτομερής και εύκολες στη κατανόηση. Το ίδιο ισχύει και για την περιγραφή της διαδικασίας του build του gem5. Επίσης, τα ερωτήματα είναι ξεκάθαρα και δεν εμπεριέχουν ασάφεια ως προς τα ζητούμενα. Σε αυτό το στάδιο δεν ήταν τόσο απαιτητικά, δεδομένου πάντα ότι υπάρχει εξοικείωση με τις γλώσσες python, C/C++ και ο φοιτητής έχει αφιερώσει χρόνο στην ανάγνωση του documentation του gem5. Συνεχίζοντας, οι πηγές και το υλικό στο οποίο παραπέμπει η εργασία να ανατρέξουμε,όπως τα tutorial για τη Markdown και το git, μας φάνηκαν πολύ χρήσιμα και συμπυκνώνουν όλες τις απαραίτητες γνώσεις για τα εργαλεία αυτά. Τέλος, η εργασία αν και εισαγωγική στον gem5, είναι εξαιρετικά ενδιαφέρουσα και μας κινητοποίησε να ψάξουμε ακόμα παραπάνω πράγματα για τις τεχνολογίες αυτές ακόμα και μετά την ολοκλήρωση της.
