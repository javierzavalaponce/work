
/*
https://johnsantic.com/comp/state.html
Writing Efficient State Machines in C
One common way of conquering difficult software design problems is to use a state machine. First you figure out all the states the software can be in. Then you determine all the inputs to the state machine—all the events that can cause the state machine to take some action or to change states. Finally you determine the state machine outputs—all the actions that the state machine can perform.
When your state machine design is done, you'll have a list of states, a list of events (inputs), and a set of action procedures for each state that describe what the state machine does for each event (outputs).
There are two ways to code a state machine in C. One way uses a set of nested switch statements. The outer switch has a case for each possible state. Each of these outer cases has an inner switch with a case for each possible event. The actual code that gets selected performs the actions for that state/event. Alternately, the outer switch could have a case for each event, and the inner switch could have a case for each state.
Another more concise way of coding is to use a lookup table. First, number all your states consecutively, starting with 0—an enum is a convenient way to do this. Do the same for your events. Then make up a set of tables, one table per state. Each table has one entry per event, in the same order as the event enum. Then the entire set of tables is arranged in the same order as the state enum. Each item in a table is the function to execute to perform the action for that particular event in that particular state.
The listing below is an example with three states and two events, and therefore six action procedures.
*/

/* Define the states and events. If your state machine program has multiple
source files, you would probably want to put these definitions in an "include"
file and #include it in each source file. This is because the action
procedures need to update current_state, and so need access to the state
definitions. */

enum states { STATE_1, STATE_2, STATE_3, MAX_STATES } current_state;
enum events { EVENT_1, EVENT_2, MAX_EVENTS } new_event;

/* Provide the fuction prototypes for each action procedure. In a real
program, you might have a separate source file for the action procedures of 
each state. Then you could create a .h file for each of the source files, 
and put the function prototypes for the source file in the .h file. Instead 
of listing the prototypes here, you would just #include the .h files. */

void action_s1_e1 (void);
void action_s1_e2 (void);
void action_s2_e1 (void);
void action_s2_e2 (void);
void action_s3_e1 (void);
void action_s3_e2 (void);
enum events get_new_event (void);

/* Define the state/event lookup table. The state/event order must be the
same as the enum definitions. Also, the arrays must be completely filled - 
don't leave out any events/states. If a particular event should be ignored in 
a particular state, just call a "do-nothing" function. */

void (*const state_table [MAX_STATES][MAX_EVENTS]) (void) = {

    { action_s1_e1, action_s1_e2 }, /* procedures for state 1 */
    { action_s2_e1, action_s2_e2 }, /* procedures for state 2 */
    { action_s3_e1, action_s3_e2 }  /* procedures for state 3 */
};

/* This is the heart of the state machine - where you execute the proper 
action procedure based on the new event you have to process and your current 
state. It's important to make sure the new event and current state are 
valid, because unlike "switch" statements, the lookup table method has no 
"default" case to catch out-of-range values. With a lookup table, 
out-of-range values cause the program to crash! */

void main (void)
{
    new_event = get_new_event (); /* get the next event to process */

    if (((new_event >= 0) && (new_event < MAX_EVENTS))
    && ((current_state >= 0) && (current_state < MAX_STATES))) {

        state_table [current_state][new_event] (); /* call the action procedure */

    } else {

        /* invalid event/state - handle appropriately */
    }
}

/* In an action procedure, you do whatever processing is required for the
particular event in the particular state. Among other things, you might have
to set a new state. */

void action_s1_e1 (void)
{
    /* do some processing here */

    current_state = STATE_2; /* set new state, if necessary */
}

void action_s1_e2 (void) {}  /* other action procedures */
void action_s2_e1 (void) {}
void action_s2_e2 (void) {}
void action_s3_e1 (void) {}
void action_s3_e2 (void) {}

/* Return the next event to process - how this works depends on your
application. */

enum events get_new_event (void)
{
    return EVENT_1;
}

