# ESP accounts and delegated permissions

The ESP account provider preserves the version-1 password database and its
existing salted hashes. Roles/rights use a separate NVS sidecar tied to each
name and salt. Legacy non-root accounts default to User plus Apps permission;
root remains root. Invalid password storage fails closed rather than resetting
credentials. Role-only changes do not rewrite password records.

`useradd NAME [admin|user]` prompts for passwords. `userrole NAME [admin|user]`
reads/sets role, and `userrights NAME [+RIGHT|-RIGHT ...]` changes delegated
rights. Names are `users`, `system`, `network`, `hardware`, `shared`, `time`,
and `apps`. New Admins default to all except hardware; Users default to apps.
Changing role resets rights to that role's defaults within the actor's grant
limit. Admin plus users permission can manage other accounts with rights no
greater than its own. It cannot edit root or elevate itself.

Password hints: `useradd` and `passwd` ask for an optional hint after the
password (in `passwd`, Enter keeps the old one and `-` removes it), and refuse
one that contains the password (`tdsh_hint_reveals`). `tdsh_user_hint_get` reads
a hint (anyone may: TinyDesk shows it at Sign in); `tdsh_user_hint_set` is
allowed for the account itself and whoever may manage it. Hints live in NVS
(`ush_users` / `hints`, up to 63 bytes each) by account name and are read only
when needed; creating or deleting an account removes a hint left under its
name, while a password change keeps it.

Every non-root role retains its home jail. Shared permission adds `/shared`;
it never opens `/root` or another home. Root-only raw memory, executable native
code, firmware/board configuration and existing per-resource ownership checks
remain protected. Port commands opt into rights with `TDSH_CMD_RIGHT(mask)`;
account commands also require `TDSH_CMD_ADMIN_ONLY`. Rights derive from the
authenticated session identity, not mutable shell variables.

Consumers set `user_role`, `user_rights` and `user_generation` in
`tdsh_core_config_t`. A session captures its account generation; password
replacement or account recreation invalidates old command/path access.
`tdsh_user_login` checks the password and creates any enabled remembered-login
proof under the same recursive provider lock. It returns the authenticated
generation; interactive login uses `tdsh_session_set_user_generation` so a
concurrent account change cannot authorize the replacement identity.

TinyDesk's native login/Users windows consume this same provider. Root controls
remembered desktop login using `bootuser NAME`, including from
`/root/.tdshrc.tdsh`. The selected account must authenticate successfully before
it can be remembered. `bootuser --require-password` disables remembering,
erases the old proof and clears pending verification. A later enable needs a
fresh successful password login. A legacy boot-user selection alone cannot
bypass the new desktop authentication gate. Standalone local-console boot
selection keeps its established behavior; desktop login policy is an additive
consumer of the provider.

The provider serializes credentials, roles, proof creation and deletion. It
rejects invalid usernames, missing accounts, escalation and root deletion.
Passwords are not accepted as `useradd` command-line arguments. These embedded
permissions are not an OS process sandbox: root/native firmware remains trusted.

Portable core permissions are tested in `tests/test_permissions.c`.
`tests/test_users_storage.c` compiles the production ESP store with in-memory
NVS/FreeRTOS shims and real mbedTLS SHA-256. To include it in standalone host
tests, configure `TDSH_BUILD_HOST=ON` and
`TDSH_TEST_MBEDTLS_DIR=/path/to/mbedtls-3.x`, then build and run CTest.
