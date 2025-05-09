let accounts = {};

function createAccount() {
    const name = document.getElementById('name').value;
    const accountNumber = document.getElementById('accountNumber').value;
    if (name && accountNumber) {
        if (accounts[accountNumber]) {
            showMessage('Account already exists!', 'text-red-500');
            return;
        }
        // Simulate C++ backend call
        accounts[accountNumber] = { name, balance: 0 };
        showMessage(`Account created for ${name}!`, 'text-green-500');
        clearForm();
    } else {
        showMessage('Please fill all fields.', 'text-red-500');
    }
}

function deposit() {
    const accountNumber = document.getElementById('accountNumber').value;
    const amount = parseFloat(document.getElementById('amount').value);
    if (!accounts[accountNumber]) {
        showMessage('Account not found!', 'text-red-500');
        return;
    }
    if (amount > 0) {
        // Simulate C++ backend call
        accounts[accountNumber].balance += amount;
        showMessage(`Deposited $${amount.toFixed(2)}! New balance: $${accounts[accountNumber].balance.toFixed(2)}`, 'text-green-500');
        clearForm();
    } else {
        showMessage('Enter a valid amount.', 'text-red-500');
    }
}

function withdraw() {
    const accountNumber = document.getElementById('accountNumber').value;
    const amount = parseFloat(document.getElementById('amount').value);
    if (!accounts[accountNumber]) {
        showMessage('Account not found!', 'text-red-500');
        return;
    }
    if (amount > 0 && amount <= accounts[accountNumber].balance) {
        // Simulate C++ backend call
        accounts[accountNumber].balance -= amount;
        showMessage(`Withdrew $${amount.toFixed(2)}! New balance: $${accounts[accountNumber].balance.toFixed(2)}`, 'text-green-500');
        clearForm();
    } else {
        showMessage('Invalid amount or insufficient funds.', 'text-red-500');
    }
}

function checkBalance() {
    const accountNumber = document.getElementById('accountNumber').value;
    if (accounts[accountNumber]) {
        showMessage(`Balance for ${accounts[accountNumber].name}: $${accounts[accountNumber].balance.toFixed(2)}`, 'text-blue-500');
    } else {
        showMessage('Account not found!', 'text-red-500');
    }
}

function showMessage(message, colorClass) {
    const messageDiv = document.getElementById('message');
    messageDiv.textContent = message;
    messageDiv.className = `mt-4 text-lg ${colorClass}`;
}

function clearForm() {
    document.getElementById('accountForm').reset();
}
