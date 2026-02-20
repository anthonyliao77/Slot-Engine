import numpy as np
import matplotlib.pyplot as plt

symbols = [
	"Cherry",
	"Lemon",
	"Orange",
	"Bell",
	"Bar",
	"LuckySeven",
	"Diamond",
	"Wild",
	"Scatter",
]

# Base weights proportional to payout values; they do not yet sum to 1.
probability = np.array(
	[
		0.1157,  # Cherry
		0.1157,  # Lemon
		0.1157,  # Orange
		0.0386,  # Bell
		0.0386,  # Bar
		0.0058,  # LuckySeven
		0.0077,  # Diamond
		0.0046,  # Wild
		0.0116,  # Scatter
	],
	dtype=float,
)

# Normalize probability
probability /= probability.sum()

##################################################### Math logic ###################################################

# Amount of spins for calculating RPM
spins = 1000
bet = 1.0
rpm_result = []
# Monte carlo simulations
sims = 10000


for i in range(sims):
    outcome = np.random.choice(symbols, size = spins, p = probability)
    payout = np.array([payout[i] for i in outcome])
    net_revenue = spins * bet - payout.sum()
    rpm_result.append(net_revenue)
    


mean_rpm = rpm_result.mean()
stdev_rpm = rpm_result.std()

##################################################### Plotting ###################################################

plt.figure(figsize=(3, 1.5))
plt.hist(rpm_result, density=True)
plt.axvline(spins, color = 'r')
plt.show()
print((rpm_result > 96).sum / sims)

