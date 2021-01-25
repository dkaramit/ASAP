var choices=[
    "GradientDescent",
    "Metropolis",
    "N-D_VEGAS",
    "NeuralNet_explain",
    "Rosenbrock",
    "DoubleExp",
    "Adaptive-Runge–Kutta",
    "Discrete_MC"
]; 

var index = Math.floor(Math.random() * choices.length);

document.write('<object class="SplitRight" id="test", type="text/html" data="./misc/');
document.write(choices[index]);
document.write('.html">');