using Enzyme

# Defining our test function
function f(x::Array{Float64}, y::Array{Float64})
    y[1] = x[1] * x[1] + x[2] * x[1]
    return nothing
end;

# To use forward-mode we then have to seed the gradient computation with
x  = [2.0, 2.0];
dx = [1.0, 0.0];
y  = [0.0];
dy = [0.0];

# Of which the second duplicated element then stores the tangent
Enzyme.autodiff(Forward, f, Duplicated(x, dx), Duplicated(y, dy))

# If we then seek to propagate multiple tangents at the same time to obtain the Hessian in one autodiff call, we then seed
# the following way
y = [0.0];
x = [2.0, 2.0];

vdy = ([0.0],[0.0]);
vdx = ([1.0, 0.0], [0.0, 1.0]);

bx = [0.0, 0.0];
by = [1.0];
vdbx = ([0.0, 0.0], [0.0, 0.0]);
vdby = ([0.0], [0.0]);

# The AD-call then takes the following form
Enzyme.autodiff(
    Forward,
    (x,y) -> Enzyme.autodiff_deferred(f, x, y),
    BatchDuplicated(Duplicated(x, bx), Duplicated.(vdx, vdbx)),
    BatchDuplicated(Duplicated(y, by), Duplicated.(vdy, vdby)),
);
