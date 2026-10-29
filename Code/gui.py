import tkinter as tk
from tkinter import ttk
import subprocess
import os


# ============================================================
# OPEN C PROGRAM IN MACOS TERMINAL
# ============================================================

def open_in_terminal(program):
    try:
        current_dir = os.getcwd()

        script = (
            'tell application "Terminal"\n'
            'activate\n'
            f'do script "cd {current_dir!r} && ./{program}"\n'
            'end tell'
        )

        subprocess.Popen([
            "osascript",
            "-e",
            script
        ])

        return True

    except Exception as e:
        return str(e)


# ============================================================
# OPEN FIFO RECEIVER + SENDER IN ONE TERMINAL
# ============================================================

def open_fifo_demo():
    try:
        current_dir = os.getcwd()

        command = (
            f"cd {current_dir!r}; "
            "./fifo_demo & "
            "sleep 1; "
            "./fifo_sender; "
            "wait"
        )

        script = (
            'tell application "Terminal"\n'
            'activate\n'
            f'do script "{command}"\n'
            'end tell'
        )

        subprocess.Popen([
            "osascript",
            "-e",
            script
        ])

        return True

    except Exception as e:
        return str(e)


# ============================================================
# DEMO FUNCTIONS
# ============================================================

def run_demo(co_title, output):

    output.delete("1.0", tk.END)

    # ========================================================
    # CO-1
    # ========================================================

    if "CO-1" in co_title:

        output.insert(
            tk.END,
            "========== CO-1 SYSTEM CALL DEMO ==========\n\n"
        )

        output.insert(
            tk.END,
            "APPLICATION LAYER\n"
            "------------------\n"
            "Linux Alarm Clock (alarm_clock.c)\n\n"
            "        ↓\n\n"
            "USER SPACE\n"
            "----------\n"
            "C Program requests OS services\n\n"
            "        ↓\n\n"
            "POSIX SYSTEM CALLS / OS INTERFACE\n"
            "----------------------------------\n\n"
        )

        system_calls = [
            ("fork()", "Create a child process for an alarm"),
            ("alarm()", "Schedule a SIGALRM timer"),
            ("pause()", "Block until a signal arrives"),
            ("kill()", "Send SIGTERM to cancel an alarm"),
            ("waitpid()", "Wait for / detect child completion"),
            ("open()", "Open or create alarm_log.txt"),
            ("read()", "Read alarm log contents"),
            ("write()", "Write alarm events to the log"),
            ("close()", "Close the file descriptor"),
        ]

        for call, purpose in system_calls:
            output.insert(
                tk.END,
                f"{call:<12} → {purpose}\n"
            )

        output.insert(
            tk.END,
            "\n        ↓\n\n"
            "KERNEL\n"
            "------\n"
            "Operating System provides the requested service\n\n"
            "        ↓\n\n"
            "RESULT\n"
            "------\n"
            "Process created / timer scheduled /\n"
            "signal delivered / file accessed\n\n"
            "============================================\n"
        )

    # ========================================================
    # CO-2
    # ========================================================

    elif "CO-2" in co_title:

        output.insert(
            tk.END,
            "========== CO-2 PROCESS DEMO ==========\n\n"
            "Launching alarm_clock...\n"
            "Opening the C program in a new Terminal window...\n\n"
        )

        result = open_in_terminal("alarm_clock")

        if result is True:

            output.insert(
                tk.END,
                "Alarm Clock launched successfully.\n\n"
                "Demonstrates:\n"
                "• fork()\n"
                "• Parent and child processes\n"
                "• Process IDs\n"
                "• Process lifecycle\n"
                "• waitpid()\n"
                "• Process scheduling\n"
            )

        else:

            output.insert(
                tk.END,
                f"Error launching Alarm Clock:\n{result}\n"
            )

    # ========================================================
    # CO-3
    # ========================================================

    elif "CO-3" in co_title:

        output.insert(
            tk.END,
            "========== CO-3 IPC / SIGNALS ==========\n\n"
            "SIGNALS IN THE ALARM CLOCK\n"
            "--------------------------\n\n"
            "SIGALRM\n"
            "  → Generated when the alarm timer expires.\n\n"
            "SIGTERM\n"
            "  → Sent by the parent to cancel an alarm.\n\n"
            "sigaction()\n"
            "  → Installs the SIGALRM signal handler.\n\n"
            "kill()\n"
            "  → Sends a signal to another process.\n\n"
            "pause()\n"
            "  → Waits for a signal to arrive.\n\n"
            "FIFO / NAMED PIPE\n"
            "  → Used for communication between processes.\n\n"
            "------------------------------------------\n"
            "Launching FIFO receiver and sender...\n"
            "------------------------------------------\n\n"
        )

        result = open_fifo_demo()

        if result is True:

            output.insert(
                tk.END,
                "FIFO IPC Demo launched successfully.\n\n"
                "The Terminal will:\n"
                "1. Start the FIFO receiver.\n"
                "2. Wait briefly for the receiver.\n"
                "3. Start the FIFO sender.\n"
                "4. Send a message through alarm_fifo.\n"
                "5. Display the received message.\n\n"
                "This demonstrates named-pipe IPC.\n"
            )

        else:

            output.insert(
                tk.END,
                f"Error launching FIFO Demo:\n{result}\n"
            )

    # ========================================================
    # CO-4
    # ========================================================

    elif "CO-4" in co_title:

        output.insert(
            tk.END,
            "========== CO-4 MEMORY DEMO ==========\n\n"
            "Launching memory_demo...\n"
            "Opening the C program in a new Terminal window...\n\n"
        )

        result = open_in_terminal("memory_demo")

        if result is True:

            output.insert(
                tk.END,
                "Memory Demo launched successfully.\n\n"
                "Concepts demonstrated:\n"
                "• Process address space\n"
                "• Global memory\n"
                "• Heap memory\n"
                "• fork()\n"
                "• Copy-on-Write\n"
                "• Parent/child memory isolation\n"
            )

        else:

            output.insert(
                tk.END,
                f"Error launching Memory Demo:\n{result}\n"
            )

    # ========================================================
    # CO-5
    # ========================================================

    elif "CO-5" in co_title:

        output.insert(
            tk.END,
            "========== CO-5 FILE I/O DEMO ==========\n\n"
            "Launching file_demo...\n"
            "Opening the File I/O demonstration in a new Terminal window...\n\n"
        )

        result = open_in_terminal("file_demo")

        if result is True:

            output.insert(
                tk.END,
                "File I/O Demo launched successfully.\n\n"
                "Demonstrates:\n"
                "• open()\n"
                "• write()\n"
                "• read()\n"
                "• close()\n"
                "• File descriptors\n"
            )

        else:

            output.insert(
                tk.END,
                f"Error launching File I/O Demo:\n{result}\n"
            )

    # ========================================================
    # CO-6
    # ========================================================

    elif "CO-6" in co_title:

        output.insert(
            tk.END,
            "========== CO-6 THREAD DEMO ==========\n\n"
            "Launching thread_demo...\n"
            "Opening the C program in a new Terminal window...\n\n"
        )

        result = open_in_terminal("thread_demo")

        if result is True:

            output.insert(
                tk.END,
                "Thread Demo launched successfully.\n\n"
                "Concepts demonstrated:\n"
                "• POSIX threads\n"
                "• Shared data\n"
                "• Mutex\n"
                "• Mutual exclusion\n"
                "• Thread synchronization\n"
            )

        else:

            output.insert(
                tk.END,
                f"Error launching Thread Demo:\n{result}\n"
            )


# ============================================================
# MAIN WINDOW
# ============================================================

root = tk.Tk()

root.title(
    "OS & System Programming - Linux Alarm Clock"
)

root.geometry(
    "1100x700"
)

root.minsize(
    900,
    600
)


# ============================================================
# COLORS / BUTTON STYLE
# ============================================================

BUTTON_BG = "#E8E8E8"
BUTTON_ACTIVE = "#D0D0D0"
BUTTON_BORDER = "#FFFFFF"
BUTTON_TEXT = "#000000"


# ============================================================
# HEADER
# ============================================================

header = tk.Frame(root)

header.pack(
    fill="x",
    padx=20,
    pady=15
)

title = tk.Label(
    header,
    text="OS & SYSTEM PROGRAMMING",
    font=("Arial", 24, "bold")
)

title.pack()

subtitle = tk.Label(
    header,
    text="Linux Alarm Clock & Operating System Concepts",
    font=("Arial", 13)
)

subtitle.pack(
    pady=5
)


# ============================================================
# NOTEBOOK
# ============================================================

notebook = ttk.Notebook(root)

notebook.pack(
    fill="both",
    expand=True,
    padx=20,
    pady=10
)


# ============================================================
# CREATE CO PAGE
# ============================================================

def create_co_page(
    co_title,
    topics,
    button_text
):

    frame = ttk.Frame(notebook)

    title_label = tk.Label(
        frame,
        text=co_title,
        font=("Arial", 20, "bold")
    )

    title_label.pack(
        pady=(25, 10)
    )

    topics_label = tk.Label(
        frame,
        text=topics,
        font=("Arial", 12),
        justify="left",
        anchor="w"
    )

    topics_label.pack(
        fill="x",
        padx=50,
        pady=15
    )

    # ========================================================
    # GLOWING BUTTON
    # ========================================================

    run_button = tk.Button(
        frame,
        text=button_text,
        font=("Arial", 13, "bold"),

        # Button size
        padx=20,
        pady=10,

        # Normal appearance
        bg=BUTTON_BG,
        fg=BUTTON_TEXT,

        # Click appearance
        activebackground=BUTTON_ACTIVE,
        activeforeground=BUTTON_TEXT,

        # Permanent glowing border
        highlightthickness=4,
        highlightbackground=BUTTON_BORDER,
        highlightcolor=BUTTON_BORDER,

        # Button border
        relief="raised",
        bd=3,

        # Prevent focus rectangle from changing appearance
        takefocus=0,

        command=lambda: run_demo(
            co_title,
            output
        )
    )

    run_button.pack(
        pady=20
    )

    output = tk.Text(
        frame,
        height=15,
        width=100,
        font=("Courier", 11)
    )

    output.pack(
        fill="both",
        expand=True,
        padx=40,
        pady=10
    )

    output.insert(
        "end",
        "Demo output will appear here...\n"
    )

    return frame


# ============================================================
# CO-1
# ============================================================

co1 = create_co_page(

    "CO-1: OS as a Service Layer",

    """Topics:
• User Space and Kernel Space
• System Calls and Kernel Services
• Shell and Command Execution
• Linux Architecture
• System Programming Fundamentals
""",

    "Run CO-1 Demonstration"

)

notebook.add(
    co1,
    text="CO-1"
)


# ============================================================
# CO-2
# ============================================================

co2 = create_co_page(

    "CO-2: Processes and Process Control",

    """Topics:
• Process Creation
• fork()
• Parent and Child Processes
• Process IDs
• Process Lifecycle
• Process Termination
• waitpid()
• Process Scheduling
""",

    "Launch Alarm Clock"

)

notebook.add(
    co2,
    text="CO-2"
)


# ============================================================
# CO-3
# ============================================================

co3 = create_co_page(

    "CO-3: IPC and Signals",

    """Topics:
• Inter-Process Communication
• Signals
• SIGALRM
• SIGTERM
• Signal Handlers
• POSIX Signal Programming
• Named Pipes (FIFO)
""",

    "Run Signal / IPC Demo"

)

notebook.add(
    co3,
    text="CO-3"
)


# ============================================================
# CO-4
# ============================================================

co4 = create_co_page(

    "CO-4: Memory Management",

    """Topics:
• Virtual Memory
• Process Address Space
• Dynamic Memory Allocation
• Copy-on-Write
• Process Creation
• Memory Isolation
""",

    "Run Memory Demo"

)

notebook.add(
    co4,
    text="CO-4"
)


# ============================================================
# CO-5
# ============================================================

co5 = create_co_page(

    "CO-5: File Systems and File I/O",

    """Topics:
• File Abstraction
• File Descriptors
• open()
• read()
• write()
• close()
• Linux File I/O System Calls
• File I/O Demonstration
""",

    "Open File I/O Demo"

)

notebook.add(
    co5,
    text="CO-5"
)


# ============================================================
# CO-6
# ============================================================

co6 = create_co_page(

    "CO-6: Concurrency and Synchronization",

    """Topics:
• Threads and Processes
• POSIX Threads
• Shared Data
• Race Conditions
• Mutex
• Mutual Exclusion
• Thread Coordination
• Synchronization
""",

    "Run Thread Demo"

)

notebook.add(
    co6,
    text="CO-6"
)


# ============================================================
# FOOTER
# ============================================================

footer = tk.Label(
    root,
    text="Linux / POSIX System Programming Project",
    font=("Arial", 10)
)

footer.pack(
    pady=8
)


# ============================================================
# START GUI
# ============================================================

root.mainloop()
