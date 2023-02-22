using Enzyme
using Printf

# Defining the square function
square(x) = x^2;

# No activity annotations
result_1 = Enzyme.autodiff(Reverse, square, 1.0)
printf("No annotations result: %f", result_1)

# No activity annotations = constant annotation
result_2 = Enzyme.autodiff(Reverse, square, Const(1.0))
printf("Equals constant annotations: %f", result_2)

# Adding activity annotations
result_3 = Enzyme.autodiff(Reverse, square, Active(1.0))
printf("Adding activity annotations: %f", result_3)